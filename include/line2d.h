#pragma once

#include <iostream>
#include "point2d.h"

class line2d
{
	friend point2d intersect(line2d p_a, line2d p_b);
	friend std::ostream &operator<<(std::ostream &p_out, const line2d &p_line2d);
public:
	double A;
	double B;
	double C;

	double x(double p_y) const;
	double y(double p_x) const;
	line2d();
	line2d(const point2d &p_a, const point2d &p_b);
	line2d(double p_ax,double p_ay,double p_bx,double p_by);
	line2d(double p_a, double p_b, double p_c);
	line2d(double p_m, double p_b);
	line2d(double p_x);
	line2d(const line2d &) = default;
	line2d &operator=(const line2d &) = default;
	~line2d() = default;
};

point2d intersect(line2d p_a, line2d p_b);
std::ostream &operator<<(std::ostream &out, const line2d &p_line2d);