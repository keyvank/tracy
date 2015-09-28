#include "buffer.h"


buffer::buffer(size_t p_width, size_t p_height) :width(p_width), height(p_height)
{
	this->color_buffer = new color[this->width*this->height];
	this->depth_buffer = new double[this->width*this->height];
}


buffer::~buffer()
{
	delete[] this->color_buffer;
	delete[] this->depth_buffer;
}
