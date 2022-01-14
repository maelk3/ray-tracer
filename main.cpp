#include <iostream>
#include "vec.h"
#include "ray.h"
#include "sphere.h"
#include "background.h"
#include "list.h"

#include "image.h"
#include <random>
#include <limits>

constexpr int NB_SAMPLES = 100;

static std::random_device rd; 
static std::mt19937 gen(rd());
static std::uniform_real_distribution<> dis(0.0, 1.0);

vec3 random_unit_vector(std::uniform_real_distribution<>& dis, std::mt19937& gen){
  float x = 2.0*dis(gen)-1.0;
  float y = 2.0*dis(gen)-1.0;
  float z = 2.0*dis(gen)-1.0;
  return vec3(x, y, z).normalize();
}

vec3 color(const Ray& ray, SurfaceList& scene){
  HitInfo hit_info;
  scene.hit(ray, 0, std::numeric_limits<float>::max(), hit_info);
  if(hit_info.mat == Material::Solid){
    return hit_info.color;
  }else{
    vec3 rand_dir = random_unit_vector(dis, gen);
    if(dot(rand_dir, hit_info.normal) < 0){
      rand_dir *= -1.0;
    }
    Ray diffusion_ray(ray.origin() + hit_info.t*ray.direction(), rand_dir);
    return 0.5*color(diffusion_ray, scene);
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

  vec3 red {1.0, 0.0, 0.0};
  vec3 blue {0.0, 0.0, 1.0};
  
  Sphere sphere1(vec3(0.0, 0.0, -1.0), red, 0.5);
  Sphere sphere2(vec3(0.0, -100.5, -1.0), blue, 100.0);
  
  BackgroundGradient bg;
  SurfaceList scene;
  scene.push_back(&sphere1);
  scene.push_back(&sphere2);
  scene.push_back(&bg);
  
  for(int j=0; j<width; j++){
    for(int i=0; i<height; i++){
      vec3 col(0.0, 0.0, 0.0);
      for(int k=0; k<NB_SAMPLES; k++){
	float u = (float(j)+dis(gen))/float(width);
	float v = (float(i)+dis(gen))/float(height);
	Ray ray(origin, low_left_corner + u*horizontal + v*vertical);
	col += color(ray, scene);
      }
      col *= 1/((float)NB_SAMPLES);
      img(i, j) = col;      
    }
  }

  img.save_as("test.bmp");
  
  return 0;
}


