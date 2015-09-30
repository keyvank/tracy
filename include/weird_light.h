#pragma once
#include "light.h"
#include "point3d.h"
#include "color.h"

class weird_light : public light
{
public:
	color calculate_color(const point3d &p_position, const point3d &p_normal) const;
	weird_light() = default;
	weird_light(const weird_light &) = delete;
	weird_light &operator=(const weird_light &) = delete;
};

