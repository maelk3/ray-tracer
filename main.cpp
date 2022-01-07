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
  Surface* sphere = new Sphere(vec3(0.0, 0.0, -1.0), red, 0.5);
  
  for(int j=0; j<width; j++){
    for(int i=0; i<height; i++){
      float u = float(j)/float(width);
      float v = float(i)/float(height);
      Ray ray(origin, low_left_corner + u*horizontal + v*vertical);
      vec3 col;
      
      unsigned char r, g, b;
      HitInfo hit_info;
      if(sphere->hit(ray, 0.0, 1000.0, hit_info)){
	col = 0.5*(hit_info.normal + vec3(1.0, 1.0, 1.0));
      }else{
	col = background_color(ray);
      }
      
      img(i, j) = col;
    }
  }

  img.save_as("test.bmp");
  
  return 0;
}


