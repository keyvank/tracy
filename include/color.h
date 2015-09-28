#pragma once

#include "point3d.h"

struct color
{
	friend color operator+(const color &, const color &);
	friend color operator*(const color &, const color &);
	friend color operator*(const color &, const double);
	friend color operator*(const color &, const point3d &);
	unsigned char B;
	unsigned char G;
	unsigned char R;
	color() = default;
	color(const color &) = default;
	color &operator=(const color &) = default;
	color(unsigned char p_r, unsigned char p_g, unsigned char p_b);
};

color operator+(const color &, const color &);
color operator*(const color &, const color &);
color operator*(const color &, const double);
color operator*(const color &, const point3d &);