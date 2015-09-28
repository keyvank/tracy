#pragma once

#include "vertex.h"
#include <vector>
#include "bitmap.h"
#include "point3d.h"
#include <string>
#include <tuple>

class mesh final
{
public:
	std::vector<vertex> vertices;
	std::vector<size_t> indices;
	std::shared_ptr<bitmap> texture;
	point2d texture_size;

	static mesh open_OBJ(const std::string &p_path);
	static mesh open_heightmap(const bitmap &p_bitmap);
	static mesh cube();
	static mesh sphere(size_t p_density);

	mesh();
	mesh(const mesh &) = default;
	mesh &operator=(const mesh &) = default;
	~mesh() = default;
};

