#pragma once

class point3d;

#include <memory>
#include <iostream>
#include <initializer_list>
#include "point3d.h"

class matrix final
{
	friend std::ostream &operator<<(std::ostream &, const matrix &);
	friend matrix operator+(matrix, const matrix &);
	friend matrix operator*(matrix, const matrix &);
private:
	double *m_data;
public:

	static matrix translate(const point3d &p_p);
	static matrix scale(const point3d &p_p);
	static matrix orthographic(double p_width,double p_height,double p_near,double p_far);
	static matrix perspective(double p_fov,double p_asp_rat,double p_near,double p_far);
	static matrix rotateX(double p_angle);
	static matrix rotateY(double p_angle);
	static matrix rotateZ(double p_angle);
	static matrix lookat(const point3d &p_eye, const point3d &p_target, const point3d &p_up);
	static matrix world(const point3d &p_position, const point3d &p_rotation, const point3d &p_size);

	matrix();
	matrix(double *p_data);
	matrix(std::initializer_list<double> p_data);
	matrix(const matrix &);
	matrix(matrix &&);
	matrix &operator=(const matrix &);
	matrix &operator=(matrix &&);
	matrix inverse() const;
	matrix transpose() const;
	double *const operator[](size_t);
	const double *const operator[](size_t) const;
	~matrix();

	matrix &operator+=(const matrix &);
	matrix &operator*=(const matrix &);
};


std::ostream &operator<<(std::ostream &, const matrix &);
matrix operator+(matrix, const matrix &);
matrix operator*(matrix, const matrix &);