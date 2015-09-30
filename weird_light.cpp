#include "weird_light.h"
#include "point3d.h"
#include "color.h"
#include <cmath>


color weird_light::calculate_color(const point3d &p_position, const point3d &p_normal) const{
	color ret(std::sin(p_position.x/10)*255,std::cos(p_position.y/10)*255,std::sin(p_position.z/10)*255);
	return ret;
}
