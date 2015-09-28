#include "renderer.h"
#include "color.h"
#include <algorithm>
#include <memory>
#include <vector>
#include "vertex.h"
#include "line2d.h"
#include "shader.h"
#include "mesh.h"

renderer::renderer(std::shared_ptr<render_target> p_target, std::shared_ptr<shader> p_shader) :m_target(p_target), m_shader(p_shader), m_buffer(new buffer(p_target->width, p_target->height)){
}

void renderer::clear(const color &p_bg_color){
	std::fill_n(this->m_buffer->color_buffer, this->m_buffer->width*this->m_buffer->height, p_bg_color);
	std::fill_n(this->m_buffer->depth_buffer, this->m_buffer->width*this->m_buffer->height, 1);
}

void renderer::draw(const mesh &p_mesh){
	this->m_shader->set_texture(p_mesh.texture);
	this->set_texture_size(p_mesh.texture_size);
	for (std::vector<size_t>::size_type i = 0; i < p_mesh.indices.size() / 3; ++i){
		rasterize(p_mesh.vertices[p_mesh.indices[i * 3]], p_mesh.vertices[p_mesh.indices[i * 3 + 1]], p_mesh.vertices[p_mesh.indices[i * 3 + 2]]);
	}
}

void renderer::render(){
	this->m_target->draw(*(this->m_buffer));
}


void renderer::rasterize_side(const line2d &p_l1, const line2d &p_l2, size_t p_h, const point3d *p_on_screen, const point3d *p_in_view, const point3d *p_in_world, const point2d *p_tex_coords, const point3d *p_normals, const color *p_cols){
	int x1 = static_cast<int>(p_l1.x(p_h)), x2 = static_cast<int>(p_l2.x(p_h));

	if (x1 > x2) std::swap(x1, x2);

	if (x1 < 0)
		x1 = 0;
	if (x1 >= static_cast<int>(this->m_buffer->width))
		x1 = this->m_buffer->width - 1;

	if (x2 < 0)
		x2 = 0;
	if (x2 >= static_cast<int>(this->m_buffer->width))
		x2 = this->m_buffer->width - 1;

	for (int i = x1; i <= x2; i++){

		point3d bc = barycentric(p_on_screen[0], p_on_screen[1], p_on_screen[2], point2d(i, p_h));
		double z = 1 / (bc.x / p_in_view[0].z + bc.y / p_in_view[1].z + bc.z / p_in_view[2].z);


		double zbuf = 1 / (bc.x / p_on_screen[0].z + bc.y / p_on_screen[1].z + bc.z / p_on_screen[2].z);
		if (zbuf>*(this->m_buffer->depth_buffer + p_h*this->m_buffer->width + i))
			continue;
		else
			*(this->m_buffer->depth_buffer + p_h*this->m_buffer->width + i) = zbuf;

		point3d bc2(bc.x*z / p_in_view[0].z, bc.y*z / p_in_view[1].z, bc.z*z / p_in_view[2].z);


		point2d texc = p_tex_coords[0] * bc2.x + p_tex_coords[1] * bc2.y + p_tex_coords[2] * bc2.z;

		point3d norm = p_normals[0] * bc2.x + p_normals[1] * bc2.y + p_normals[2] * bc2.z;
		norm.normalize();

		point3d wr = p_in_world[0] * bc2.x + p_in_world[1] * bc2.y + p_in_world[2] * bc2.z;

		color col = p_cols[0] * bc2.x + p_cols[1] * bc2.y + p_cols[2] * bc2.z;

		vertex ret(wr, norm, texc, col);

		*(this->m_buffer->color_buffer + p_h*this->m_buffer->width + i) = this->m_shader->shade_pixel(ret);
	}
}


void renderer::rasterize(const vertex &p_a, const vertex &p_b, const vertex &p_c){
	if (this->m_buffer){

		point3d screen(this->m_buffer->width, this->m_buffer->height, 1);

		point3d in_world[3] = { this->m_world*p_a.position, this->m_world*p_b.position, this->m_world*p_c.position };

		point3d in_view[3] = { this->m_view*in_world[0], this->m_view*in_world[1], this->m_view*in_world[2] };

		if (in_view[0].z >= 0 || in_view[1].z >= 0 || in_view[2].z >= 0){
			// Cannot draw! Fix the bug please!
			return;
		}

		point3d on_screen[3] = { ((this->m_world_view_projection*p_a.position + 1)*screen / 2),
			((this->m_world_view_projection*p_b.position + 1)*screen / 2),
			(this->m_world_view_projection*p_c.position + 1)*screen / 2 };

		if (this->m_backface_culling_enabled){
			point3d norm = cross(on_screen[1] - on_screen[0], on_screen[2] - on_screen[0]);
			if (norm.z < 0)
				return;
		}

		point3d normal_in_world[3]{this->m_normal_world*p_a.normal, this->m_normal_world*p_b.normal, this->m_normal_world*p_c.normal};
		for (size_t i = 0; i<3; i++) normal_in_world[i].normalize();

		color cols[3]{p_a.col, p_b.col, p_c.col};

		point2d tex_coords[3]{ p_a.tex_coord*this->m_texture_size, p_b.tex_coord*this->m_texture_size, p_c.tex_coord*this->m_texture_size };

		size_t inds[3]{0, 1, 2};

		std::sort(std::begin(inds), std::end(inds), [&on_screen](const size_t &p_a, const size_t &p_b){return on_screen[p_a].y > on_screen[p_b].y; });

		line2d l1(on_screen[inds[0]], on_screen[inds[1]]);
		line2d l2(on_screen[inds[0]], on_screen[inds[2]]);
		line2d l3(on_screen[inds[1]], on_screen[inds[2]]);

		int h1 = static_cast<int>(on_screen[inds[0]].y), h2 = static_cast<int>(on_screen[inds[1]].y), h3 = static_cast<int>(on_screen[inds[2]].y);

		if (h1 < 0)h1 = 0; else if (static_cast<size_t>(h1) >= this->m_buffer->height)h1 = this->m_buffer->height - 1;
		if (h2 < 0)h2 = 0; else if (static_cast<size_t>(h2) >= this->m_buffer->height)h2 = this->m_buffer->height - 1;
		if (h3 < 0)h3 = 0; else if (static_cast<size_t>(h3) >= this->m_buffer->height)h3 = this->m_buffer->height - 1;

		for (int h = h1; h > h2; h--){
			rasterize_side(l1, l2, h, on_screen, in_view, in_world, tex_coords, normal_in_world, cols);
		}

		for (int h = h2; h > h3; h--){
			rasterize_side(l2, l3, h, on_screen, in_view, in_world, tex_coords, normal_in_world, cols);
		}

	}
}

void renderer::set_world(const matrix &p_world){
	this->m_world = p_world;
	this->m_normal_world = p_world.inverse().transpose();
	this->m_world_view_projection = this->m_projection*this->m_view*this->m_world;
}

void renderer::set_backface_culling(bool p_enabled){
	this->m_backface_culling_enabled = p_enabled;
}

void renderer::set_view(const matrix &p_view){
	this->m_view = p_view;
	this->m_world_view_projection = this->m_projection*this->m_view*this->m_world;
}

void renderer::set_projection(const matrix &p_proj){
	this->m_projection = p_proj;
	this->m_world_view_projection = this->m_projection*this->m_view*this->m_world;
}

void renderer::set_texture_size(const point2d &p_texture_size){
	this->m_texture_size = p_texture_size;
}