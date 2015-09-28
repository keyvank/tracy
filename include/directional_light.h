#pragma once

#include "light.h"
#include "point3d.h"
#include "color.h"

class directional_light : public light
{
public:
	color col;
	point3d direction;
	color calculate_color(const point3d &p_position, const point3d &p_normal) const;
	directional_light() = delete;
	directional_light(const color &p_col,const point3d &p_direction);
	directional_light(const directional_light &) = delete;
	directional_light &operator=(const directional_light &) = delete;
};

