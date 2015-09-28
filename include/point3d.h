#pragma once

class matrix;
class point2d;

#include "point2d.h"
#include "matrix.h"
#include <iostream>

class point3d final
{

	friend std::ostream &operator<<(std::ostream &, const point3d &);

	friend point3d operator*(const matrix &, const point3d &);
	friend point3d operator+(const point3d &, const point3d &);
	friend point3d operator*(const point3d &, const point3d &);
	friend point3d operator-(const point3d &, const point3d &);

	friend point3d operator+(const point3d &, double);
	friend point3d operator-(const point3d &, double);
	friend point3d operator*(const point3d &, double);
	friend point3d operator/(const point3d &, double);
	friend point3d operator/(double,const point3d &);

public:
	double x;
	double y;
	double z;
	double length();
	void normalize();
	point3d() = default;
	point3d(double p_v);
	point3d(double p_x,double p_y,double p_z);
	point3d(const point3d &) = default;
	point3d &operator=(const point3d &) = default;
	point3d &operator+=(const point3d &);
	point3d &operator*=(const point3d &);
	point3d &operator-=(const point3d &);
	operator point2d() const;
	~point3d() = default;
};

double distance(const point3d &p_a, const point3d &p_b);

point3d cross(const point3d &p_a, const point3d &p_b);
double dot(const point3d &p_a, const point3d &p_b);

std::ostream &operator<<(std::ostream &, const point3d &);

point3d operator*(const matrix &, const point3d &);
point3d operator+(const point3d &, const point3d &);
point3d operator*(const point3d &, const point3d &);
point3d operator-(const point3d &, const point3d &);

point3d operator+(const point3d &, double);
point3d operator-(const point3d &, double);
point3d operator*(const point3d &, double);
point3d operator/(const point3d &, double);
point3d operator/(double, const point3d &);