#pragma once

#include "light.h"
#include "point3d.h"
#include "color.h"


class point_light : public light
{
public:
	color col;
	point3d position;
	double power;
	double range;
	color calculate_color(const point3d &p_position, const point3d &p_normal) const;
	point_light() = delete;
	point_light(const color &p_col, const point3d &p_position, double p_power, double p_range);
	point_light(const point_light &) = delete;
	point_light &operator=(const point_light &) = delete;
};

