#include "bitmap_target.h"
#include "color.h"
#include <fstream>

bitmap_target::bitmap_target(const size_t p_width, const size_t p_height, const std::string& p_path) :render_target(p_width, p_height), m_file_header(), m_info_header(), path(p_path){

	size_t filesize = 54 + 3 * this->width*this->height;

	this->m_file_header[0] = 'B';
	this->m_file_header[1] = 'M';
	this->m_file_header[2] = (unsigned char)(filesize);
	this->m_file_header[3] = (unsigned char)(filesize >> 8);
	this->m_file_header[4] = (unsigned char)(filesize >> 16);
	this->m_file_header[5] = (unsigned char)(filesize >> 24);
	this->m_file_header[10] = 54;

	this->m_info_header[0] = 40;
	this->m_info_header[4] = (unsigned char)(this->width);
	this->m_info_header[5] = (unsigned char)(this->width >> 8);
	this->m_info_header[6] = (unsigned char)(this->width >> 16);
	this->m_info_header[7] = (unsigned char)(this->width >> 24);
	this->m_info_header[8] = (unsigned char)(this->height);
	this->m_info_header[9] = (unsigned char)(this->height >> 8);
	this->m_info_header[10] = (unsigned char)(this->height >> 16);
	this->m_info_header[11] = (unsigned char)(this->height >> 24);
	this->m_info_header[12] = 1;
	this->m_info_header[14] = 24;
}

void bitmap_target::draw(const buffer &p_buffer){
	std::ofstream out(path, std::ios::out | std::ios::binary);
	out.write(reinterpret_cast<const char*>(this->m_file_header), 14);
	out.write(reinterpret_cast<const char*>(this->m_info_header), 40);

	unsigned char bmppad[3] = { 0, 0, 0 };

	for (size_t i = 0; i < this->height; i++)
	{
		out.write(reinterpret_cast<const char*>(p_buffer.color_buffer) + (this->width*i * 3), 3 * this->width);
		out.write(reinterpret_cast<const char*>(bmppad), (4 - (this->width * 3) % 4) % 4);
	}
	out.close();
}