#pragma once

#include <string>
#include "color.h"
#include "point2d.h"

class bitmap final
{
public:
	size_t width;
	size_t height;
	color uv(const point2d &p_tex_coord);
	color * data;

	bitmap(const std::string &p_path);
	bitmap(const bitmap &) = delete;
	bitmap &operator=(const bitmap &) = delete;
	color *const operator[](size_t p_index);
	const color *const operator[](size_t p_index) const;

	~bitmap();
};

