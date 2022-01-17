
OBJECTS=main.o vec.o ray.o image.o sphere.o list.o surface.o shader.o preview.o texture.o
CXXFLAGS= -std=c++11 -pthread -lGLEW -lglut -lGL

ray_tracer: $(OBJECTS)
	g++ $(CXXFLAGS) -o ray_tracer $(OBJECTS)

main.o: vec.h ray.h

vec.o: image.h

image.o:

ray.o: vec.h

sphere.o: vec.h sphere.h surface.h

surface.o: vec.h surface.h texture.h

list.o: list.h vec.h surface.h

preview.o: preview.h image.h

shader.o: shader.h

texture.o: vec.h

.PHONY: clean, run

clean:
	rm $(OBJECTS) ray_tracer test.bmp

run: ray_tracer
	(time ./ray_tracer)
