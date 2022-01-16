#include <iostream>
#include "vec.h"
#include "ray.h"
#include "sphere.h"
#include "list.h"

#include "image.h"
#include <random>
#include <limits>

constexpr int NB_SAMPLES = 1000;
constexpr int MAX_DEPTH = 200;

static std::random_device rd; 
static std::mt19937 gen(rd());
static std::uniform_real_distribution<> dis(0.0, 1.0);

vec3 random_unit_vector(std::uniform_real_distribution<>& dis, std::mt19937& gen){
  float x = 2.0*dis(gen)-1.0;
  float y = 2.0*dis(gen)-1.0;
  float z = 2.0*dis(gen)-1.0;
  return vec3(x, y, z).normalize();
}

vec3 color(const Ray& ray, SurfaceList& scene, int depth){
  HitInfo hit_info;
  if(!scene.hit(ray, 0.001, std::numeric_limits<float>::max(), hit_info)){
    vec3 dir = unit_vector(ray.direction());
    float t = 0.5*(dir.y()+1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
  }else{
    Ray scattered;
    vec3 attenuation;
    if(depth < MAX_DEPTH && hit_info.mat->scatter(ray, hit_info, attenuation, scattered)){
      return attenuation*color(scattered, scene, depth+1);
    }else{
      return vec3(0.0, 0.0, 0.0);
    }
  }
}

int main(){

  int width = 400;
  int height = 200;

  Image img(width, height);

  vec3 low_left_corner {-2.0, -1.0, -1.0};
  vec3 horizontal {4.0, 0.0, 0.0};
  vec3 vertical {0.0, 2.0, 0.0};
  vec3 origin {0.0, 0.0, 0.0};

  Sphere sphere1(vec3(0.0, 0.0, -1.0), 0.5, new Lambertian(vec3(0.8, 0.3, 0.3)));
  Sphere sphere2(vec3(0.0, -100.5, -1.0), 100.0, new Lambertian(vec3(0.8, 0.8, 0.0)));
  Sphere sphere3(vec3(1.0, 0.0, -1.0), 0.5, new Lambertian(vec3(0.8, 0.6, 0.2)));
  Sphere sphere4(vec3(-1.0, 0.0, -1.0), 0.5, new Lambertian(vec3(0.8, 0.8, 0.8)));
  
  SurfaceList scene;
  scene.push_back(&sphere1);
  scene.push_back(&sphere2);  
  scene.push_back(&sphere3);
  scene.push_back(&sphere4);
  
  for(int j=0; j<width; j++){
    for(int i=0; i<height; i++){
      vec3 col(0.0, 0.0, 0.0);
      for(int k=0; k<NB_SAMPLES; k++){
	float u = (float(j)+dis(gen))/float(width);
	float v = (float(i)+dis(gen))/float(height);
	Ray ray(origin, low_left_corner + u*horizontal + v*vertical);
	col += color(ray, scene, 0);
      }
      col *= 1/((float)NB_SAMPLES);
      img(i, j) = col;      
    }
  }

  img.save_as("test.bmp");
  
  return 0;
}


