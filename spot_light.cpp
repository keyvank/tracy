#include "spot_light.h"
#include <cmath>


spot_light::spot_light(const color &p_col, const point3d &p_position, double p_power, double p_range, const point3d &p_direction, double p_angle, double p_sharpness) :point_light(p_col, p_position, p_power, p_range), direction(p_direction), angle(p_angle), sharpness(p_sharpness){}

color spot_light::calculate_color(const point3d &p_position, const point3d &p_normal) const{
	throw std::runtime_error("Spot light is not implemented!");
}

