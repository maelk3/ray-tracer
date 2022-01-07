
OBJECTS=main.o vec.o ray.o

ray_tracer: $(OBJECTS)
	g++ -o ray_tracer -std=c++11 $(OBJECTS) && ./ray_tracer

main.o: vec.h ray.h

ray.o: vec.h
