
OBJECTS=main.o vec.o ray.o image.o sphere.o

ray_tracer: $(OBJECTS)
	g++ -o ray_tracer -std=c++11 $(OBJECTS) && ./ray_tracer && feh -Z --force-aliasing test.bmp

main.o: vec.h ray.h

image.o: image.h

ray.o: vec.h

sphere.o: vec.h ray.h

.PHONY: clean

clean:
	rm $(OBJECTS) ray_tracer test.bmp
