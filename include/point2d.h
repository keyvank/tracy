#pragma once

class matrix;

#include "matrix.h"
#include <iostream>

class point2d final
{

	friend std::ostream &operator<<(std::ostream &, const point2d &);

	friend point2d operator+(const point2d &, const point2d &);
	friend point2d operator*(const point2d &, const point2d &);
	friend point2d operator-(const point2d &, const point2d &);

	friend point2d operator+(const point2d &, double);
	friend point2d operator-(const point2d &, double);
	friend point2d operator*(const point2d &, double);
	friend point2d operator/(const point2d &, double);
	friend point2d operator/(double, const point2d &);

public:
	double x;
	double y;
	double length();
	void normalize();
	point2d() = default;
	point2d(double p_v);
	point2d(double p_x, double p_y);
	point2d(const point2d &) = default;
	point2d &operator=(const point2d &) = default;
	point2d &operator+=(const point2d &);
	point2d &operator*=(const point2d &);
	point2d &operator-=(const point2d &);
	~point2d() = default;
};

double distance(const point2d &p_a, const point2d &p_b);

point3d barycentric(const point2d &p_a, const point2d &p_b, const point2d &p_c, const point2d &p_r);

std::ostream &operator<<(std::ostream &, const point2d &);

point2d operator+(const point2d &, const point2d &);
point2d operator*(const point2d &, const point2d &);
point2d operator-(const point2d &, const point2d &);

point2d operator+(const point2d &, double);
point2d operator-(const point2d &, double);
point2d operator*(const point2d &, double);
point2d operator/(const point2d &, double);
point2d operator/(double, const point2d &);