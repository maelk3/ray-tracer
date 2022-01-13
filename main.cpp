#include <iostream>
#include "vec.h"
#include "ray.h"
#include "sphere.h"
#include "background.h"
#include "list.h"

#include "image.h"
#include <random>

constexpr int NB_SAMPLES = 50;

vec3 background_color(const Ray& ray){
  vec3 dir = unit_vector(ray.direction());
  float t = 0.5*(dir.y()+1.0);
  return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main(){

  std::random_device rd; 
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, 1.0);

  int width = 800;
  int height = 400;

  Image img(width, height);

  vec3 low_left_corner {-2.0, -1.0, -1.0};
  vec3 horizontal {4.0, 0.0, 0.0};
  vec3 vertical {0.0, 2.0, 0.0};
  vec3 origin {0.0, 0.0, 0.0};

  vec3 red {1.0, 0.0, 0.0};
  Sphere sphere1(vec3(0.0, 0.0, -1.0), red, 0.5);
  Sphere sphere2(vec3(1.0, 0.5, -2), red, 0.8);
  
  BackgroundGradient bg;
  SurfaceList list;
  list.push_back(&sphere1);
  list.push_back(&sphere2);
  list.push_back(&bg);
  
  for(int j=0; j<width; j++){
    for(int i=0; i<height; i++){
      vec3 col(0.0, 0.0, 0.0);
      for(int k=0; k<NB_SAMPLES; k++){
	float u = (float(j)+dis(gen))/float(width);
	float v = (float(i)+dis(gen))/float(height);
	Ray ray(origin, low_left_corner + u*horizontal + v*vertical);
      
	unsigned char r, g, b;
	HitInfo hit_info;
	list.hit(ray, 0, 100000000, hit_info);
	col += hit_info.color;
      }
      col *= 1/((float)NB_SAMPLES);
      img(i, j) = col;      
    }
  }

  img.save_as("test.bmp");
  
  return 0;
}


