#pragma once

#include "normal_shader.h"
#include <vector>
#include "light.h"

class light_shader:public normal_shader
{
protected:
	color shade_pixel(const vertex &p_vertex);
public:
	std::vector<std::shared_ptr<light>> lights;
	light_shader();
	light_shader(const light_shader &) = delete;
	light_shader &operator=(const light_shader &) = delete;
	~light_shader() = default;
};

