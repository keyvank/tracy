#pragma once

#include "color.h"
#include "vertex.h"
#include "buffer.h"
#include "shader.h"
#include <memory>

class normal_shader:public shader
{
protected:
	color shade_pixel(const vertex &p_vertex);
public:
	normal_shader();
	normal_shader(const normal_shader &) = delete;
	normal_shader &operator=(const normal_shader &) = delete;
	~normal_shader() = default;
};
