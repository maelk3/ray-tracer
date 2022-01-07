
OBJECTS=main.o vec.o ray.o image.o sphere.o

ray_tracer: $(OBJECTS)
	g++ -o ray_tracer -std=c++11 $(OBJECTS) && ./ray_tracer && feh -Z --force-aliasing test.bmp

main.o: vec.h ray.h

vec.o: image.h

image.o:

ray.o: vec.h

sphere.o: vec.h sphere.h surface.h

.PHONY: clean

clean:
	rm $(OBJECTS) ray_tracer test.bmp
