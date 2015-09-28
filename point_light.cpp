#include "point_light.h"
#include "point3d.h"
#include "color.h"


point_light::point_light(const color &p_col, const point3d &p_position, double p_power, double p_range) :col(p_col), position(p_position), power(p_power), range(p_range){}

double DotProduct(point3d lightPos, point3d pos3D, point3d normal)
{
	point3d lightDir = (pos3D - lightPos);
	lightDir.normalize();
	double ret = dot(point3d(0, 0, 0) - lightDir, normal);
	return ret>0 ? ret : 0;
}

const double a_a = 0.0;
const double a_b = 0.1;
const double a_c = 1.0;


color point_light::calculate_color(const point3d &p_position, const point3d &p_normal) const{
	double f = DotProduct(this->position, p_position, p_normal)*this->power;
	double dist = distance(p_position, this->position);
	double atten = 1.0f / ((a_a * dist * dist) + (a_b * dist) + a_c);
	atten = step(dist, this->range)*atten;
	return this->col*saturate(f*atten);
}






