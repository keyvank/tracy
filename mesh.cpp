#include "mesh.h"
#include <string>
#include <fstream>
#include "utilities.h"
#include <cmath>


mesh::mesh() :texture_size(1, 1){}

mesh mesh::cube(){
	mesh ret;
	ret.vertices.reserve(36);
	ret.indices.reserve(36);
	ret.vertices.push_back(vertex(point3d(0.5, -0.5, -0.5), point3d(0, 0, 0), point2d(1, 0)));
	ret.vertices.push_back(vertex(point3d(-0.5, -0.5, -0.5),point3d(0,0,0),point2d(0,0)));
	ret.vertices.push_back(vertex(point3d(-0.5, 0.5, -0.5), point3d(0, 0, 0), point2d(0, 1)));
	ret.vertices.push_back(vertex(point3d(0.5, -0.5, -0.5), point3d(0, 0, 0), point2d(1, 0)));
	ret.vertices.push_back(vertex(point3d(-0.5, 0.5, -0.5), point3d(0, 0, 0), point2d(0, 1)));
	ret.vertices.push_back(vertex(point3d(0.5, 0.5, -0.5), point3d(0, 0, 0), point2d(1, 1)));

	
	ret.vertices.push_back(vertex(point3d(-0.5, -0.5, 0.5), point3d(0, 0, 0), point2d(0, 0)));
	ret.vertices.push_back(vertex(point3d(0.5, -0.5, 0.5), point3d(0, 0, 0), point2d(1, 0)));
	ret.vertices.push_back(vertex(point3d(-0.5, 0.5, 0.5), point3d(0, 0, 0), point2d(0, 1)));
	ret.vertices.push_back(vertex(point3d(-0.5, 0.5, 0.5), point3d(0, 0, 0), point2d(0, 1)));
	ret.vertices.push_back(vertex(point3d(0.5, -0.5, 0.5), point3d(0, 0, 0), point2d(1, 0)));
	ret.vertices.push_back(vertex(point3d(0.5, 0.5, 0.5), point3d(0, 0, 0), point2d(1, 1)));

	ret.vertices.push_back(vertex(point3d(-0.5, -0.5, -0.5), point3d(0, 0, 0), point2d(0, 0)));
	ret.vertices.push_back(vertex(point3d(0.5, -0.5, -0.5), point3d(0, 0, 0), point2d(1, 0)));
	ret.vertices.push_back(vertex(point3d(-0.5, -0.5, 0.5), point3d(0, 0, 0), point2d(0, 1)));
	ret.vertices.push_back(vertex(point3d(-0.5, -0.5, 0.5), point3d(0, 0, 0), point2d(0, 1)));
	ret.vertices.push_back(vertex(point3d(0.5, -0.5, -0.5), point3d(0, 0, 0), point2d(1, 0)));
	ret.vertices.push_back(vertex(point3d(0.5, -0.5, 0.5), point3d(0, 0, 0), point2d(1, 1)));

	ret.vertices.push_back(vertex(point3d(0.5, 0.5, -0.5), point3d(0, 0, 0), point2d(1, 0)));
	ret.vertices.push_back(vertex(point3d(-0.5, 0.5, -0.5), point3d(0, 0, 0), point2d(0, 0)));
	ret.vertices.push_back(vertex(point3d(-0.5, 0.5, 0.5), point3d(0, 0, 0), point2d(0, 1)));
	ret.vertices.push_back(vertex(point3d(0.5, 0.5, -0.5), point3d(0, 0, 0), point2d(1, 0)));
	ret.vertices.push_back(vertex(point3d(-0.5, 0.5, 0.5), point3d(0, 0, 0), point2d(0, 1)));
	ret.vertices.push_back(vertex(point3d(0.5, 0.5, 0.5), point3d(0, 0, 0), point2d(1, 1)));

	ret.vertices.push_back(vertex(point3d(-0.5, 0.5, -0.5), point3d(0, 0, 0), point2d(1, 0)));
	ret.vertices.push_back(vertex(point3d(-0.5, -0.5, -0.5), point3d(0, 0, 0), point2d(0, 0)));
	ret.vertices.push_back(vertex(point3d(-0.5, -0.5, 0.5), point3d(0, 0, 0), point2d(0, 1)));
	ret.vertices.push_back(vertex(point3d(-0.5, 0.5, -0.5), point3d(0, 0, 0), point2d(1, 0)));
	ret.vertices.push_back(vertex(point3d(-0.5, -0.5, 0.5), point3d(0, 0, 0), point2d(0, 1)));
	ret.vertices.push_back(vertex(point3d(-0.5, 0.5, 0.5), point3d(0, 0, 0), point2d(1, 1)));

	ret.vertices.push_back(vertex(point3d(0.5, -0.5, -0.5), point3d(0, 0, 0), point2d(0, 0)));
	ret.vertices.push_back(vertex(point3d(0.5, 0.5, -0.5), point3d(0, 0, 0), point2d(1, 0)));
	ret.vertices.push_back(vertex(point3d(0.5, -0.5, 0.5), point3d(0, 0, 0), point2d(0, 1)));
	ret.vertices.push_back(vertex(point3d(0.5, -0.5, 0.5), point3d(0, 0, 0), point2d(0, 1)));
	ret.vertices.push_back(vertex(point3d(0.5, 0.5, -0.5), point3d(0, 0, 0), point2d(1, 0)));
	ret.vertices.push_back(vertex(point3d(0.5, 0.5, 0.5), point3d(0, 0, 0), point2d(1, 1)));

	for (size_t i = 0; i < ret.vertices.size()/3; i++){
		ret.indices.push_back(i*3);
		ret.indices.push_back(i * 3+1);
		ret.indices.push_back(i * 3+2);
	}
	return ret;
}


mesh mesh::open_OBJ(const std::string &p_path){
	mesh ret;
	std::ifstream file(p_path, std::ios::binary | std::ios::in);
	std::string tmp;
	while (file>>tmp){
		if (tmp == "v"){
			double a, b, c;
			file >> a >> b >> c;
			ret.vertices.push_back(vertex(point3d(a, b, c)));
		}
		if (tmp == "f"){
			std::string a, b, c;
			file >> a >> b >> c;
			ret.indices.push_back(std::stoi(a) - 1);
			ret.indices.push_back(std::stoi(b) - 1);
			ret.indices.push_back(std::stoi(c) - 1);
		}
	}
	return ret;
}


mesh mesh::open_heightmap(const bitmap &p_bitmap){
	mesh ret;
	ret.vertices.reserve(p_bitmap.height*p_bitmap.width);
	for (size_t i = 0; i < p_bitmap.height; i++){
		for (size_t j = 0; j < p_bitmap.width; j++){
			double x = static_cast<double>(j) / p_bitmap.width - 0.5;
			double y = static_cast<double>(i) / p_bitmap.height - 0.5;
			double h = (p_bitmap[i][j].R + p_bitmap[i][j].G + p_bitmap[i][j].B) / 3.0;
			double z =  h / 255.0 - 0.5;
			ret.vertices.push_back(vertex(point3d(x,z,y)));
		}
	}
	for (size_t i = 0; i < p_bitmap.height-1; i++){
		for (size_t j = 0; j < p_bitmap.width - 1; j++){
			ret.indices.push_back(i*p_bitmap.height + j);
			ret.indices.push_back(i*p_bitmap.height + j + 1);
			ret.indices.push_back((i + 1)*p_bitmap.height + j);

			ret.indices.push_back((i + 1)*p_bitmap.height + j + 1);
			ret.indices.push_back((i + 1)*p_bitmap.height + j);
			ret.indices.push_back(i*p_bitmap.height + j + 1);
		}
	}
	return ret;
}

mesh mesh::sphere(size_t p_density){
	mesh ret;
	double step = PI * 2 / p_density;
	double stepx = 0;
	double stepy = 0;
	double tex = 1.0 / p_density;
	for (size_t i = 0; i <= p_density; i++)
	{
		double rad = (double)sin(stepy);
		for (size_t j = 0; j <= p_density; j++)
		{
			ret.vertices.push_back(vertex(point3d(rad * sin(stepx) * 1 / 2.0, cos(stepy) * 1 / 2.0 , rad * cos(stepx) * 1 / 2.0), point3d(0, 0, 0), point2d(tex * j, tex * i)));
			stepx += step;
		}
		stepx = 0;
		stepy += step / 2;
	}
	for (size_t i = 0; i < p_density; i++)
	{
		for (size_t j = 0; j < p_density; j++)
		{
			int ii = i + 1;
			int jj = j + 1;
			ret.indices.push_back(jj + i * (p_density + 1));
			ret.indices.push_back(j + i * (p_density + 1));
			ret.indices.push_back(jj + ii * (p_density + 1));
			ret.indices.push_back(j + i * (p_density + 1));
			ret.indices.push_back(j + ii * (p_density + 1));
			ret.indices.push_back(jj + ii * (p_density + 1));
		}
	}
	return ret;
}