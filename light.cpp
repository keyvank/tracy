#include "light.h"

double light::step(double p_x, double p_y){
	return p_y >= p_x;
}

double light::saturate(double p_f){
	if (p_f > 1)return 1;
	else if (p_f < 0) return 0;
	else return p_f;
}