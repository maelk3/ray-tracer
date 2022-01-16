
OBJECTS=main.o vec.o ray.o image.o sphere.o list.o surface.o
CXXFLAGS= -std=c++11

ray_tracer: $(OBJECTS)
	c++ -o ray_tracer $(OBJECTS) && ./ray_tracer && feh -Z --force-aliasing test.bmp

main.o: vec.h ray.h

vec.o: image.h

image.o:

ray.o: vec.h

sphere.o: vec.h sphere.h surface.h

surface.o: vec.h surface.h

list.o: list.h vec.h surface.h

.PHONY: clean

clean:
	rm $(OBJECTS) ray_tracer test.bmp
