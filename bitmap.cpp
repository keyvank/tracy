#include "bitmap.h"

#include <string>
#include <fstream>


bitmap::bitmap(const std::string &p_path)
{
	std::ifstream file(p_path, std::ios::binary | std::ios::in);
	char info[54];
	file.read(info, 54);
	this->width = *reinterpret_cast<int *>(&info[18]);
	this->height = *reinterpret_cast<int *>(&info[22]);
	this->data = new color[this->width*this->height];
	file.read(reinterpret_cast<char*>(this->data), this->width*this->height * 3);
}

color bitmap::uv(const point2d &p_tex_coord){
	int u = (int)(p_tex_coord.x * this->width);
	int v = static_cast<int>(p_tex_coord.y * this->height);
	u = u % this->width;
	v = v % this->height;
	return (*this)[v][u];
}


color *const bitmap::operator[](size_t p_index){
	return &data[p_index*this->width];
}

const color *const bitmap::operator[](size_t p_index) const{
	return &data[p_index*this->width];
}

bitmap::~bitmap(){
	delete[] this->data;
}
