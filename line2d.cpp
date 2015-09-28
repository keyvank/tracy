#include "line2d.h"
#include "point3d.h"
#include <iostream>
#include <exception>
#include <cmath>

line2d::line2d(double p_ax,double p_ay,double p_bx,double p_by){
	if (p_ax == p_bx){
		if (p_ay != p_by){
			A = 1; B = 0; C = -p_ax;
		}
		else{
			A = 0; B = 0; C = 0;
		}
	}
	else
	{
		double m = (p_by - p_ay) / (p_bx - p_ax);
		double b = -m*p_ax + p_ay;
		A = -m; B = 1; C = -b;
	}
}

line2d::line2d(const point2d &p_a, const point2d &p_b){
	if (p_a.x == p_b.x){
		if (p_a.y != p_b.y){
			A = 1; B = 0; C = -p_a.x;
		}
		else{
			A = 0; B = 0; C = 0;
		}
	}
	else
	{
		double m = (p_b.y - p_a.y) / (p_b.x - p_a.x);
		double b = -m*p_a.x + p_a.y;
		A = -m; B = 1; C = -b;
	}
}

line2d::line2d():A(-1),B(1),C(0){

}
line2d::line2d(double p_a, double p_b, double p_c):A(p_a),B(p_b),C(p_c){

}
line2d::line2d(double p_m, double p_b):A(-p_m),B(1),C(-p_b){

}
line2d::line2d(double p_x):A(1),B(0),C(-p_x){

}

double line2d::y(double p_x) const{
	return -A*p_x / B - C / B;
}
double line2d::x(double p_y) const{
	return -B*p_y / A - C / A;
}

point2d intersect(line2d p_a, line2d p_b){
	if (p_a.B != 0 && p_b.B != 0){
		double r = -p_a.B / p_b.B;
		p_b.A *= r; p_b.A += p_a.A;
		p_b.B *= r; p_b.B += p_a.B;
		p_b.C *= r; p_b.C += p_a.C;
		if (p_b.A != 0){
			double x = -p_b.C / p_b.A;
			return point2d(x, p_a.y(x));
		}
		else
			throw std::runtime_error("No intersection!");
	}
	else{
		if (p_a.B == 0 && p_b.B == 0) throw std::runtime_error("No intersection!");
		else if (p_a.B == 0){
			double x = -p_a.C / p_a.A;
			return point2d(x, p_b.y(x));
		}
		else{
			double x = -p_b.C / p_b.A;
			return point2d(x, p_a.y(x));
		}
	}
}

std::ostream &operator<<(std::ostream &out, const line2d &l){
	out << l.A << "X + " << l.B << "Y + " << l.C << " = 0";
	return out;
}