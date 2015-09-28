class matrix;

#include "point3d.h"
#include "matrix.h"
#include <cmath>


point3d::point3d(double p_x, double p_y, double p_z):x(p_x),y(p_y),z(p_z){
}
point3d::point3d(double p_v) : x(p_v), y(p_v), z(p_v){
}

point3d &point3d::operator+=(const point3d &p_p){
	this->x += p_p.x;
	this->y += p_p.y;
	this->z += p_p.z;
	return *this;
}
point3d &point3d::operator*=(const point3d &p_p){
	this->x *= p_p.x;
	this->y *= p_p.y;
	this->z *= p_p.z;
	return *this;
}


point3d &point3d::operator-=(const point3d &p_p){
	this->x -= p_p.x;
	this->y -= p_p.y;
	this->z -= p_p.z;
	return *this;
}


point3d operator+(const point3d &p_a, const point3d &p_b){
	point3d ret = p_a;
	ret += p_b;
	return ret;
}
point3d operator*(const point3d &p_a, const point3d &p_b){
	point3d ret = p_a;
	ret *= p_b;
	return ret;
}

point3d operator-(const point3d &p_a, const point3d &p_b){
	point3d ret = p_a;
	ret -= p_b;
	return ret;
}

point3d operator+(const point3d &p_a, double p_b){
	point3d ret = p_a;
	ret.x += p_b; ret.y += p_b; ret.z += p_b; 
	return ret;
}
point3d operator-(const point3d &p_a, double p_b){
	point3d ret = p_a;
	ret.x -= p_b; ret.y -= p_b; ret.z -= p_b; 
	return ret;
}
point3d operator*(const point3d &p_a, double p_b){
	point3d ret = p_a;
	ret.x *= p_b; ret.y *= p_b; ret.z *= p_b;
	return ret;
}
point3d operator/(const point3d &p_a, double p_b){
	point3d ret = p_a;
	ret.x /= p_b; ret.y /= p_b; ret.z /= p_b; 
	return ret;
}
point3d operator/(double p_a,const point3d &p_b){
	point3d ret = p_b;
	ret.x = p_a / ret.x; ret.y = p_a / ret.y; ret.z = p_a / ret.z;
	return ret;
}

point3d operator*(const matrix &p_matrix, const point3d &p_p){
	point3d ret;
	double w = p_matrix[3][0] * p_p.x + p_matrix[3][1] * p_p.y + p_matrix[3][2] * p_p.z + p_matrix[3][3] * 1;
	ret.x = (p_matrix[0][0] * p_p.x + p_matrix[0][1] * p_p.y + p_matrix[0][2] * p_p.z + p_matrix[0][3] * 1) / w;
	ret.y = (p_matrix[1][0] * p_p.x + p_matrix[1][1] * p_p.y + p_matrix[1][2] * p_p.z + p_matrix[1][3] * 1) / w;
	ret.z = (p_matrix[2][0] * p_p.x + p_matrix[2][1] * p_p.y + p_matrix[2][2] * p_p.z + p_matrix[2][3] * 1) / w;
	return ret;
}

void point3d::normalize(){
	double len = this->length();
	this->x /= len;
	this->y /= len;
	this->z /= len;
}

double point3d::length(){
	return sqrt(x*x + y*y + z*z);
}


double distance(const point3d &p_a, const point3d &p_b){
	return sqrt((p_a.z - p_b.z)*(p_a.z - p_b.z) + (p_a.y - p_b.y)*(p_a.y - p_b.y) + (p_a.x - p_b.x)*(p_a.x - p_b.x));
}

point3d cross(const point3d &p_a, const point3d &p_b){
	return point3d(p_a.y * p_b.z - p_a.z * p_b.y,
		p_a.z * p_b.x - p_a.x * p_b.z,
		p_a.x * p_b.y - p_a.y * p_b.x);
}
double dot(const point3d &p_a, const point3d &p_b){
	return p_a.x*p_b.x + p_a.y*p_b.y + p_a.z*p_b.z;
}

std::ostream &operator<<(std::ostream &p_out, const point3d &p_p){
	p_out << "(" << p_p.x << ", " << p_p.y << ", " << p_p.z << ")";
	return p_out;
}

point3d::operator point2d() const{
	return point2d(this->x, this->y);
}
