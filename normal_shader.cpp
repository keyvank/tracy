#include "normal_shader.h"
#include "color.h"

normal_shader::normal_shader(){}

color normal_shader::shade_pixel(const vertex &p_vertex){
	if (this->m_texture)
		return p_vertex.col * this->m_texture->uv(p_vertex.tex_coord);
	else
		return p_vertex.col;
}