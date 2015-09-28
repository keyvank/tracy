#include "color.h"
#include "point3d.h"


color::color(unsigned char p_r, unsigned char p_g, unsigned char p_b):B(p_b),G(p_g),R(p_r){

}

color operator+(const color &p_a, const color &p_b){
	int R = static_cast<int>(p_a.R + p_b.R);
	int G = static_cast<int>(p_a.G + p_b.G);
	int B = static_cast<int>(p_a.B + p_b.B);
	R = R<0 ? 0 : (R>255 ? 255 : R);
	G = G<0 ? 0 : (G>255 ? 255 : G);
	B = B<0 ? 0 : (B>255 ? 255 : B);
	return color(R, G, B);

}
color operator*(const color &p_a, const color &p_b){
	int R = static_cast<int>((p_a.R * p_b.R) / 255);
	int G = static_cast<int>((p_a.G * p_b.G) / 255);
	int B = static_cast<int>((p_a.B * p_b.B) / 255);
	R = R<0 ? 0 : (R>255 ? 255 : R);
	G = G<0 ? 0 : (G>255 ? 255 : G);
	B = B<0 ? 0 : (B>255 ? 255 : B);
	return color(R, G, B);

}
color operator*(const color &p_a, const double b){
	int R = static_cast<int>(p_a.R * b);
	int G = static_cast<int>(p_a.G * b);
	int B = static_cast<int>(p_a.B * b);
	R = R<0 ? 0 : (R>255 ? 255 : R);
	G = G<0 ? 0 : (G>255 ? 255 : G);
	B = B<0 ? 0 : (B>255 ? 255 : B);
	return color(R, G, B);
}
color operator*(const color &p_a, const point3d &b){
	int R = static_cast<int>(p_a.R * b.x);
	int G = static_cast<int>(p_a.G * b.y);
	int B = static_cast<int>(p_a.B * b.z);
	R = R<0 ? 0 : (R>255 ? 255 : R);
	G = G<0 ? 0 : (G>255 ? 255 : G);
	B = B<0 ? 0 : (B>255 ? 255 : B);
	return color(R, G, B);
}
