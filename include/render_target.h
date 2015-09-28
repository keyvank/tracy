#pragma once

#include <vector>
#include "color.h"
#include "buffer.h"

class render_target
{
	friend class renderer;
public:
	const size_t width;
	const size_t height;
	virtual void draw(const buffer &p_data) = 0;
	render_target(const size_t p_width,const size_t p_height);
	render_target(const render_target &) = delete;
	render_target &operator=(const render_target &) = delete;
	virtual ~render_target() = default;
};

