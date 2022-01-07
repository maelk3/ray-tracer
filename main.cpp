#include <iostream>
#include "vec.h"
#include "ray.h"
#include "sphere.h"

#include "image.h"


vec3 background_color(const Ray& ray){
  vec3 dir = unit_vector(ray.direction());
  float t = 0.5*(dir.y()+1.0);
  return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main(){

  int width = 400;
  int height = 200;

  Image img(width, height);

  vec3 low_left_corner {-2.0, -1.0, -1.0};
  vec3 horizontal {4.0, 0.0, 0.0};
  vec3 vertical {0.0, 2.0, 0.0};
  vec3 origin {0.0, 0.0, 0.0};

  vec3 red {1.0, 0.0, 0.0};
  Sphere sphere(vec3(0.0, 0.0, -1.0), red, 0.5);
  
  for(int j=0; j<width; j++){
    for(int i=0; i<height; i++){
      float u = float(j)/float(width);
      float v = float(i)/float(height);
      Ray ray(origin, low_left_corner + u*horizontal + v*vertical);
      vec3 col;
      
      unsigned char r, g, b;
      if(sphere.intersect(ray)){
	col = sphere.color();
	vec3 hit = sphere.hit_point(ray);
	vec3 normal = (hit-sphere.center()).normalize();
	col = 0.5*(normal + vec3(1.0, 1.0, 1.0));
      }else{
	col = background_color(ray);
      }
      r = (unsigned char)(255*col.r());
      g = (unsigned char)(255*col.g());
      b = (unsigned char)(255*col.b());			           
      img(i, j) = {b, g, r};
    }
  }

  img.save_as("test.bmp");
  
  return 0;
}


