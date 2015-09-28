#include "directional_light.h"
#include "point3d.h"
#include "color.h"
#include <exception>


directional_light::directional_light(const color &p_col, const point3d &p_direction) :col(p_col), direction(p_direction){}


color directional_light::calculate_color(const point3d &p_position, const point3d &p_normal) const{
	double s = dot(point3d(0, 0, 0) - this->direction, p_normal);
	return this->col*s;
}


