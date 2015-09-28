#include "ambient_light.h"
#include "point3d.h"
#include "color.h"


ambient_light::ambient_light(const color &p_col) :col(p_col){}


color ambient_light::calculate_color(const point3d &p_position, const point3d &p_normal) const{
	return this->col;
}






