#include "shader.h"
#include "vertex.h"
#include "matrix.h"
#include "buffer.h"
#include "color.h"
#include "line2d.h"
#include <memory>
#include <algorithm>


void shader::set_texture(std::shared_ptr<bitmap> p_texture){
	this->m_texture = p_texture;
}

shader::shader(){}