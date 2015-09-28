#include "vertex.h"
#include "point3d.h"
#include "color.h"

vertex::vertex(const point3d &p_position, const point3d &p_normal, const point2d &p_tex_coord, const color &p_col) :position(p_position), normal(p_normal), tex_coord(p_tex_coord), col(p_col)
{
}
