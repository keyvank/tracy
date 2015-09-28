#pragma once

#include "point3d.h"
#include "render_target.h"
#include "color.h"
#include <memory>
#include <vector>
#include "shader.h"
#include "vertex.h"
#include "buffer.h"
#include "bitmap.h"
#include "mesh.h"

class renderer
{
protected:
	std::shared_ptr<render_target> m_target;
	std::shared_ptr<shader> m_shader;
	std::shared_ptr<buffer> m_buffer;
	void rasterize_side(const line2d &p_l1, const line2d &p_l2, size_t p_h, const point3d *p_on_screen, const point3d *p_in_view, const point3d *p_in_world, const point2d *p_tex_coords, const point3d *p_normals, const color *p_cols);
	void rasterize(const vertex &p_a, const vertex &p_b, const vertex &p_c);
	
	matrix m_normal_world;
	matrix m_world;
	matrix m_view;
	matrix m_projection;
	matrix m_world_view_projection;
	point2d m_texture_size;
	bool m_backface_culling_enabled;
public:
	virtual void draw(const mesh &p_mesh);
	virtual void clear(const color &p_bg_color);
	void render();
	void set_texture(std::shared_ptr<bitmap> p_texture);
	void set_texture_size(const point2d &p_texture_size);
	void set_world(const matrix &p_world);
	void set_view(const matrix &p_view);
	void set_projection(const matrix &p_proj);
	void set_backface_culling(bool p_enabled);
	renderer() = delete;
	renderer(std::shared_ptr<render_target> p_target,std::shared_ptr<shader> p_shader);
	renderer(const renderer &) = delete;
	renderer &operator=(const renderer &) = delete;
	virtual ~renderer() = default;
};

