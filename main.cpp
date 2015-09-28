#include <iostream>
#include <string>
#include <memory>
#include "matrix.h"
#include "bitmap_target.h"
#include "line2d.h"
#include "shader.h"
#include "light_shader.h"
#include "point3d.h"
#include "point_light.h"
#include "spot_light.h"
#include "ambient_light.h"
#include "directional_light.h"
#include "mesh.h"
#include "utilities.h"
#include <cmath>

using namespace std;

#define TRACY_PATH (string("./files/"))

#define FRAME_PATH (TRACY_PATH+"output.bmp")
#define BOX_TEXTURE_PATH (TRACY_PATH+"box.bmp")
#define TEAPOT_PATH (TRACY_PATH+"teapot.obj")

#define QUALITY 2
#define WIDTH (800*QUALITY)
#define HEIGHT (600*QUALITY)

#define TEAPOT_POSITION (point3d(0,-50,-20))
#define TEAPOT_SIZE (point3d(40))
#define BOX_POSITION (point3d(0,0,0))
#define BOX_SIZE (point3d(100,100,300))
#define BOX_TEXTURE_SIZE (point2d(2,2))

#define CAMERA_POSITION (point3d(0,0,160))

#define POINTLIGHT_POSITION (point3d(0,10,30))
#define POINTLIGHT_COLOR (color(255,255,255))
#define POINTLIGHT_POWER (5)
#define POINTLIGHT_RANGE (700)

#define AMBIENT_LIGHT (color(30,30,30))

#define NEAR 0.01
#define FAR 10000


int main(int argc, char **argv){
	try{
		shared_ptr<render_target> target(new bitmap_target(WIDTH, HEIGHT, FRAME_PATH));
		shared_ptr<light_shader> shader(new light_shader());
		renderer engine(target, shader);
		double aspect_ratio = target->width / (double)target->height;
		engine.set_projection(matrix::perspective(PI / 4, aspect_ratio, NEAR, FAR));

		mesh box = mesh::cube();
		change_winding(box);
		calculate_normals(box);
		shared_ptr<bitmap> tex(new bitmap(BOX_TEXTURE_PATH));
		box.texture = tex;
		box.texture_size = BOX_TEXTURE_SIZE;

		mesh teapot = mesh::open_OBJ(TEAPOT_PATH);
		calculate_normals(teapot);

		shader->lights.push_back(make_shared<point_light>(POINTLIGHT_COLOR, POINTLIGHT_POSITION, POINTLIGHT_POWER, POINTLIGHT_RANGE));
		shader->lights.push_back(make_shared<ambient_light>(AMBIENT_LIGHT));

		engine.clear(color(0, 0, 0));
		engine.set_view(matrix::translate(point3d(0, 0, 0) - CAMERA_POSITION));

		cout << "Rendering..." << endl;
		engine.set_world(matrix::world(BOX_POSITION, 0, BOX_SIZE));
		engine.draw(box);

		engine.set_world(matrix::world(TEAPOT_POSITION, 0, TEAPOT_SIZE));
		engine.draw(teapot);

		engine.render();
		cout << "Rendered! (" << FRAME_PATH << ")" << endl;
	}
	catch (const exception &ex){
		cout << "An error occurred: " << ex.what();
	}
	return 0;
}
