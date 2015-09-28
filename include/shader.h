#pragma once

#include <memory>
#include "buffer.h"
#include "vertex.h"
#include "matrix.h"
#include "bitmap.h"
#include "line2d.h"
#include "point3d.h"
#include "color.h"

class shader
{
protected:
	std::shared_ptr<bitmap> m_texture;
public:
	virtual color shade_pixel(const vertex &p_vertex) = 0;
	void set_texture(std::shared_ptr<bitmap> p_texture);
	shader();
	shader(const shader &) = delete;
	shader &operator=(const shader &) = delete;
	virtual ~shader() = default;
};

