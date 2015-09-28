class matrix;

#include "point2d.h"
#include "matrix.h"
#include <cmath>


point2d::point2d(double p_x, double p_y) :x(p_x), y(p_y){
}
point2d::point2d(double p_v) : x(p_v), y(p_v){
}

point2d &point2d::operator+=(const point2d &p_p){
	this->x += p_p.x;
	this->y += p_p.y;
	return *this;
}
point2d &point2d::operator*=(const point2d &p_p){
	this->x *= p_p.x;
	this->y *= p_p.y;
	return *this;
}


point2d &point2d::operator-=(const point2d &p_p){
	this->x -= p_p.x;
	this->y -= p_p.y;
	return *this;
}


point2d operator+(const point2d &p_a, const point2d &p_b){
	point2d ret = p_a;
	ret += p_b;
	return ret;
}
point2d operator*(const point2d &p_a, const point2d &p_b){
	point2d ret = p_a;
	ret *= p_b;
	return ret;
}

point2d operator-(const point2d &p_a, const point2d &p_b){
	point2d ret = p_a;
	ret -= p_b;
	return ret;
}

point2d operator+(const point2d &p_a, double p_b){
	point2d ret = p_a;
	ret.x += p_b; ret.y += p_b;
	return ret;
}
point2d operator-(const point2d &p_a, double p_b){
	point2d ret = p_a;
	ret.x -= p_b; ret.y -= p_b;
	return ret;
}
point2d operator*(const point2d &p_a, double p_b){
	point2d ret = p_a;
	ret.x *= p_b; ret.y *= p_b;	
	return ret;
}
point2d operator/(const point2d &p_a, double p_b){
	point2d ret = p_a;
	ret.x /= p_b; ret.y /= p_b;
	return ret;
}
point2d operator/(double p_a, const point2d &p_b){
	point2d ret = p_b;
	ret.x = p_a / ret.x; ret.y = p_a / ret.y;	return ret;
}

void point2d::normalize(){
	double len = this->length();
	this->x /= len;
	this->y /= len;
}

double point2d::length(){
	return sqrt(x*x + y*y);
}


double distance(const point2d &p_a, const point2d &p_b){
	return sqrt((p_a.y - p_b.y)*(p_a.y - p_b.y) + (p_a.x - p_b.x)*(p_a.x - p_b.x));
}

point3d barycentric(const point2d &p_a, const point2d &p_b, const point2d &p_c, const point2d &p_r){

	double l1 = ((p_b.y - p_c.y)*(p_r.x - p_c.x) + (p_c.x - p_b.x)*(p_r.y - p_c.y)) / ((p_b.y - p_c.y)*(p_a.x - p_c.x) + (p_c.x - p_b.x)*(p_a.y - p_c.y));
	double l2 = ((p_c.y - p_a.y)*(p_r.x - p_c.x) + (p_a.x - p_c.x)*(p_r.y - p_c.y)) / ((p_c.y - p_a.y)*(p_b.x - p_c.x) + (p_a.x - p_c.x)*(p_b.y - p_c.y));
	double l3 = 1 - l1 - l2;
	return point3d(l1, l2, l3);
}

std::ostream &operator<<(std::ostream &p_out, const point2d &p_p){
	p_out << "(" << p_p.x << ", " << p_p.y << ")";
	return p_out;
}

