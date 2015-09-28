#pragma once

#include "point3d.h"
#include "color.h"

class light
{
protected:
	static double saturate(double p_f);
	static double step(double p_x, double p_y);
public:
	virtual color calculate_color(const point3d &p_position, const point3d &p_normal) const = 0;
	light() = default;
	light(const light &) = delete;
	light &operator=(const light &) = delete;
	virtual ~light() = default;
};

