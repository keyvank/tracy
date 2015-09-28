#include "matrix.h"
#include <algorithm>
#include <iostream>
#include <initializer_list>
#include "point3d.h"

matrix::matrix() :m_data(new double[16]{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 })
{
}

matrix::matrix(double *p_data) : m_data(new double[16])
{
	std::copy_n(p_data, 16, this->m_data);
}

matrix::matrix(const matrix &p_matrix):m_data(new double[16]){
	std::copy_n(p_matrix.m_data, 16, this->m_data);
}

matrix::matrix(matrix &&p_matrix) : m_data(p_matrix.m_data){
	p_matrix.m_data = nullptr;
}

matrix::matrix(std::initializer_list<double> p_data):m_data(new double[16]){
	std::copy(p_data.begin(), p_data.end(), this->m_data);
}

matrix &matrix::operator=(const matrix &p_matrix){
	std::copy_n(p_matrix.m_data, 16, this->m_data);
	return *this;
}

matrix &matrix::operator=(matrix &&p_matrix){
	this->m_data = p_matrix.m_data;
	p_matrix.m_data = nullptr;
	return *this;
}

matrix::~matrix(){
	delete[] this->m_data;
}

double *const matrix::operator[](size_t p_index){
	return m_data + p_index * 4;
}

const double *const matrix::operator[](size_t p_index) const{
	return m_data + p_index * 4;
}

std::ostream &operator<<(std::ostream &p_out, const matrix &p_matrix){
	p_out << '[';
	std::for_each(p_matrix.m_data, p_matrix.m_data + 16, [&p_out](double val){p_out << val << ','; });
	p_out << ']';
	return p_out;
}

matrix &matrix::operator+=(const matrix &p_matrix){
	for (size_t i = 0; i < 16; i++)
		this->m_data[i] += p_matrix.m_data[i];
	return *this;
}

matrix operator+(matrix p_a, const matrix &p_b){
	p_a += p_b;
	return p_a;
}

matrix &matrix::operator*=(const matrix &p_matrix){
	matrix product;
	for (size_t i = 0; i < 4; i++){
		for (size_t j = 0; j < 4; j++){
			double sum = 0;
			for (size_t k = 0; k < 4; k++){
				sum += (*this)[i][k] * (p_matrix[k][j]);
			}
			product[i][j] = sum;
		}
	}
	*this = std::move(product);
	return *this;
}

matrix operator*(matrix p_a, const matrix &p_b){
	p_a *= p_b;
	return p_a;
}


matrix matrix::orthographic(double p_width,double p_height,double p_near,double p_far){
	return matrix{ 1 / p_width, 0, 0, 0, 0, 1 / p_height, 0, 0, 0, 0, -2 / (p_far - p_near), -(p_far + p_near) / (p_far - p_near), 0, 0, 0, 1 };
}
matrix matrix::perspective(double p_fov,double p_asp_rat, double p_near, double p_far){
	return matrix{ 1 / tan(p_fov / 2) / p_asp_rat, 0, 0, 0, 0, 1 / tan(p_fov / 2), 0, 0, 0, 0, -(p_far + p_near) / (p_far - p_near), -2 * p_far*p_near / (p_far - p_near), 0, 0, -1, 0 };
}

matrix matrix::scale(const point3d &p_p){
	return matrix{ p_p.x, 0, 0, 0, 0, p_p.y, 0, 0, 0, 0, p_p.z, 0, 0, 0, 0, 1 };
}
matrix matrix::translate(const point3d &p_p){
	return matrix{ 1, 0, 0, p_p.x, 0, 1, 0, p_p.y, 0, 0, 1, p_p.z, 0, 0, 0, 1 };
}

matrix matrix::rotateX(double p_angle){
	return matrix{ 1, 0, 0, 0, 0, cos(p_angle), -sin(p_angle), 0, 0, sin(p_angle), cos(p_angle), 0, 0, 0, 0, 1 };
}
matrix matrix::rotateY(double p_angle){
	return matrix{ cos(p_angle), 0, sin(p_angle), 0, 0, 1, 0, 0, -sin(p_angle),0, cos(p_angle), 0, 0, 0, 0, 1 };
}
matrix matrix::rotateZ(double p_angle){
	return matrix{ cos(p_angle), -sin(p_angle), 0, 0, sin(p_angle), cos(p_angle), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
}

matrix matrix::lookat(const point3d &p_eye, const point3d &p_target, const point3d &p_up){
	point3d zaxis = p_eye-p_target;
	zaxis.normalize();
	point3d xaxis = cross(p_up, zaxis);
	xaxis.normalize();
	point3d yaxis = cross(zaxis, xaxis);

	matrix orientation = {
		xaxis.x, yaxis.x, zaxis.x, 0,
		xaxis.y, yaxis.y, zaxis.y, 0,
		xaxis.z, yaxis.z, zaxis.z, 0,
		0, 0, 0, 1
	};

	matrix translation = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-p_eye.x, -p_eye.y, -p_eye.z, 1
	};

	return (orientation * translation);
}

matrix matrix::world(const point3d &p_position, const point3d &p_rotation, const point3d &p_size){
	return matrix::translate(p_position)*matrix::rotateZ(p_rotation.z)*matrix::rotateY(p_rotation.y)*matrix::rotateX(p_rotation.x)*matrix::scale(p_size);
}


matrix matrix::transpose() const{
	matrix ret;
	for (size_t i = 0; i < 4; i++){
		for (size_t j = 0; j < 4; j++){
			ret[j][i] = (*this)[i][j];
		}
	}
	return ret;
}

matrix matrix::inverse() const{
	double *m = this->m_data;
	double inv[16], det;
	int i;

	inv[0] = m[5] * m[10] * m[15] -
		m[5] * m[11] * m[14] -
		m[9] * m[6] * m[15] +
		m[9] * m[7] * m[14] +
		m[13] * m[6] * m[11] -
		m[13] * m[7] * m[10];

	inv[4] = -m[4] * m[10] * m[15] +
		m[4] * m[11] * m[14] +
		m[8] * m[6] * m[15] -
		m[8] * m[7] * m[14] -
		m[12] * m[6] * m[11] +
		m[12] * m[7] * m[10];

	inv[8] = m[4] * m[9] * m[15] -
		m[4] * m[11] * m[13] -
		m[8] * m[5] * m[15] +
		m[8] * m[7] * m[13] +
		m[12] * m[5] * m[11] -
		m[12] * m[7] * m[9];

	inv[12] = -m[4] * m[9] * m[14] +
		m[4] * m[10] * m[13] +
		m[8] * m[5] * m[14] -
		m[8] * m[6] * m[13] -
		m[12] * m[5] * m[10] +
		m[12] * m[6] * m[9];

	inv[1] = -m[1] * m[10] * m[15] +
		m[1] * m[11] * m[14] +
		m[9] * m[2] * m[15] -
		m[9] * m[3] * m[14] -
		m[13] * m[2] * m[11] +
		m[13] * m[3] * m[10];

	inv[5] = m[0] * m[10] * m[15] -
		m[0] * m[11] * m[14] -
		m[8] * m[2] * m[15] +
		m[8] * m[3] * m[14] +
		m[12] * m[2] * m[11] -
		m[12] * m[3] * m[10];

	inv[9] = -m[0] * m[9] * m[15] +
		m[0] * m[11] * m[13] +
		m[8] * m[1] * m[15] -
		m[8] * m[3] * m[13] -
		m[12] * m[1] * m[11] +
		m[12] * m[3] * m[9];

	inv[13] = m[0] * m[9] * m[14] -
		m[0] * m[10] * m[13] -
		m[8] * m[1] * m[14] +
		m[8] * m[2] * m[13] +
		m[12] * m[1] * m[10] -
		m[12] * m[2] * m[9];

	inv[2] = m[1] * m[6] * m[15] -
		m[1] * m[7] * m[14] -
		m[5] * m[2] * m[15] +
		m[5] * m[3] * m[14] +
		m[13] * m[2] * m[7] -
		m[13] * m[3] * m[6];

	inv[6] = -m[0] * m[6] * m[15] +
		m[0] * m[7] * m[14] +
		m[4] * m[2] * m[15] -
		m[4] * m[3] * m[14] -
		m[12] * m[2] * m[7] +
		m[12] * m[3] * m[6];

	inv[10] = m[0] * m[5] * m[15] -
		m[0] * m[7] * m[13] -
		m[4] * m[1] * m[15] +
		m[4] * m[3] * m[13] +
		m[12] * m[1] * m[7] -
		m[12] * m[3] * m[5];

	inv[14] = -m[0] * m[5] * m[14] +
		m[0] * m[6] * m[13] +
		m[4] * m[1] * m[14] -
		m[4] * m[2] * m[13] -
		m[12] * m[1] * m[6] +
		m[12] * m[2] * m[5];

	inv[3] = -m[1] * m[6] * m[11] +
		m[1] * m[7] * m[10] +
		m[5] * m[2] * m[11] -
		m[5] * m[3] * m[10] -
		m[9] * m[2] * m[7] +
		m[9] * m[3] * m[6];

	inv[7] = m[0] * m[6] * m[11] -
		m[0] * m[7] * m[10] -
		m[4] * m[2] * m[11] +
		m[4] * m[3] * m[10] +
		m[8] * m[2] * m[7] -
		m[8] * m[3] * m[6];

	inv[11] = -m[0] * m[5] * m[11] +
		m[0] * m[7] * m[9] +
		m[4] * m[1] * m[11] -
		m[4] * m[3] * m[9] -
		m[8] * m[1] * m[7] +
		m[8] * m[3] * m[5];

	inv[15] = m[0] * m[5] * m[10] -
		m[0] * m[6] * m[9] -
		m[4] * m[1] * m[10] +
		m[4] * m[2] * m[9] +
		m[8] * m[1] * m[6] -
		m[8] * m[2] * m[5];

	det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

	det = 1.0f / det;



	for (i = 0; i < 16; i++)
		inv[i] *= det;

	return matrix(inv);
}