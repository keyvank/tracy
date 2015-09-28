#pragma once
#include "point_light.h"
#include "light.h"
#include "point3d.h"
#include "color.h"

class spot_light : public point_light
{
public:
	point3d direction;
	double angle;
	double sharpness;
	color calculate_color(const point3d &p_position, const point3d &p_normal) const;
	spot_light() = delete;
	spot_light(const color &p_col, const point3d &p_position, double p_power, double p_range, const point3d &p_direction, double p_angle,double p_sharpness);
	spot_light(const spot_light &) = delete;
	spot_light &operator=(const spot_light &) = delete;
};

