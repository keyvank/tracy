
#include "mesh.h"
#include "point3d.h"
#include <vector>

void calculate_normals(mesh &p_mesh){
	for (std::vector<size_t>::size_type i = 0; i < p_mesh.indices.size() / 3; i++)
	{
		size_t index1 = p_mesh.indices[i * 3];
		size_t index2 = p_mesh.indices[i * 3 + 1];
		size_t index3 = p_mesh.indices[i * 3 + 2];

		point3d side1 = p_mesh.vertices[index2].position - p_mesh.vertices[index1].position;
		point3d side2 = p_mesh.vertices[index3].position - p_mesh.vertices[index1].position;
		point3d normal = cross(side1, side2);

		p_mesh.vertices[index1].normal += normal;
		p_mesh.vertices[index2].normal += normal;
		p_mesh.vertices[index3].normal += normal;
	}

	for (std::vector<size_t>::size_type i = 0; i < p_mesh.vertices.size(); i++)
		p_mesh.vertices[i].normal.normalize();
}

void change_winding(mesh &p_mesh){
	for (std::vector<size_t>::size_type i = 0; i < p_mesh.indices.size() / 3; i++)
	{
		std::swap(p_mesh.indices[i * 3], p_mesh.indices[i * 3 + 1]);
	}
}