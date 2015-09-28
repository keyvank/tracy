#pragma once

#include "light.h"
#include "point3d.h"
#include "color.h"

class ambient_light : public light
{
public:
	color col;
	color calculate_color(const point3d &p_position, const point3d &p_normal) const;
	ambient_light() = delete;
	ambient_light(const color &p_col);
	ambient_light(const ambient_light &) = delete;
	ambient_light &operator=(const ambient_light &) = delete;
};

