CC=g++
CFLAGS=-Wall -std=gnu++11
INCLUDE=include
SOURCE=./src/

all: main.o ambient_light.o bitmap.o bitmap_target.o buffer.o color.o directional_light.o light.o light_shader.o line2d.o matrix.o mesh.o normal_shader.o point2d.o point3d.o point_light.o renderer.o render_target.o shader.o spot_light.o utilities.o vertex.o weird_light.o
	$(CC) $(CFLAGS) main.o ambient_light.o bitmap.o bitmap_target.o buffer.o color.o directional_light.o light.o light_shader.o line2d.o matrix.o mesh.o normal_shader.o point2d.o point3d.o point_light.o renderer.o render_target.o shader.o spot_light.o utilities.o vertex.o weird_light.o -o ./tracy

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INCLUDE)

clean:
	rm -rf *.o
	rm -f ./tracy
	rm -f ./files/output.bmp
