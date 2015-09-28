#pragma once

#include "color.h"

struct buffer
{
	size_t width;
	size_t height;
	double *depth_buffer;
	color *color_buffer;
	buffer(size_t p_width, size_t p_height);
	buffer(const buffer &) = delete;
	buffer &operator=(const buffer &) = delete;
	~buffer();
};

