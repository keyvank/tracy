#pragma once

#include "render_target.h"
#include "color.h"
#include "renderer.h"
#include <vector>
#include <string>
#include "buffer.h"




class bitmap_target : public render_target
{
private:
	unsigned char m_file_header[14];
	unsigned char m_info_header[40];
public:
	const std::string path;
	void draw(const buffer &p_buffer) override;
	bitmap_target(const size_t p_width,const size_t p_height,const std::string& p_path);
	bitmap_target(const bitmap_target &) = delete;
	bitmap_target &operator=(const bitmap_target &) = delete;
	~bitmap_target() = default;
};

