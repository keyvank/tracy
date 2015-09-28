#include "light_shader.h"
#include "normal_shader.h"
#include "color.h"
#include "light.h"


light_shader::light_shader() :normal_shader(),lights(){}


color light_shader::shade_pixel(const vertex &p_vertex){
	
	color total_light(0, 0, 0);
	for (std::shared_ptr<light> l : lights){
		total_light = total_light + l->calculate_color(p_vertex.position, p_vertex.normal);
	}

	if (this->m_texture)
		return p_vertex.col * total_light * this->m_texture->uv(p_vertex.tex_coord);
	else
		return p_vertex.col * total_light;
}