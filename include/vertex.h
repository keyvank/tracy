#pragma once

#include "point3d.h"
#include "point2d.h"
#include "color.h"

class vertex
{
public:
	point3d position;
	point3d normal;
	point2d tex_coord;
	color col;

	vertex(const point3d &p_position, const point3d &p_normal = point3d(0, 0, 0), const point2d &p_tex_coord = point2d(0, 0), const color &p_col = color(255, 255, 255));
	vertex(const vertex &) = default;
	vertex &operator=(const vertex &) = default;
	~vertex() = default;
};

