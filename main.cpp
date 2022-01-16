#include <iostream>
#include <random>
#include <limits>
#include <thread>
#include <functional>

#include "vec.h"
#include "ray.h"
#include "sphere.h"
#include "list.h"
#include "preview.h"

#include "image.h"

constexpr int NB_SAMPLES = 1000;
constexpr int MAX_DEPTH = 200;
constexpr int NB_THREADS = 6;

constexpr int WIDTH = 400;
constexpr int HEIGHT = 200;

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

void render_rectangle(int i_min, int i_max, int j_min, int j_max, SurfaceList& scene, vec3 low_left_corner, vec3 horizontal, vec3 vertical, vec3 origin, Image& img){
  for(int i=i_max-1; i>=i_min; i--){
    for(int j=j_min; j<j_max; j++){
      vec3 col(0.0, 0.0, 0.0);
      for(int k=0; k<NB_SAMPLES; k++){
	float u = (float(j)+random_uniform())/float(WIDTH);
	float v = (float(i)+random_uniform())/float(HEIGHT);
	Ray ray(origin, low_left_corner + u*horizontal + v*vertical);
	col += color(ray, scene, 0);
      }
      col *= 1/((float)NB_SAMPLES);
      img(i, j) = col;      
    }
  }
}

static Image img(WIDTH, HEIGHT);

int main(){

  vec3 low_left_corner {-2.0, -1.0, -1.0};
  vec3 horizontal {4.0, 0.0, 0.0};
  vec3 vertical {0.0, 2.0, 0.0};
  vec3 origin {0.0, 0.0, 0.0};

  Sphere sphere1(vec3(0.0, 0.0, -1.0), 0.5, new Lambertian(vec3(0.2, 0.1, 1.0)));
  Sphere sphere2(vec3(0.0, -100.5, -1.0), 100.0, new Lambertian(vec3(0.07, 0.8, 0.1)));
  Sphere sphere3(vec3(1.0, 0.0, -1.0), 0.5, new Metal(vec3(0.8, 0.5, 0.0), 0.5));
  Sphere sphere4(vec3(-1.0, 0.0, -1.0), 0.5, new Metal(vec3(0.8, 0.8, 0.8), 0.3));
  Sphere sphere5(vec3(-0.5, -0.4, -0.7), 0.2, new Metal(vec3(1.0, 0.0, 1.0), 1.0));
  
  SurfaceList scene;
  scene.push_back(&sphere1);
  scene.push_back(&sphere2);  
  scene.push_back(&sphere3);
  scene.push_back(&sphere4);
  scene.push_back(&sphere5);
  std::thread  threads[NB_THREADS];
  float nb_rows = (float)HEIGHT/(float)NB_THREADS;
  for(int l=0; l<NB_THREADS; l++){
    threads[l] = std::thread{render_rectangle, (int)(l*nb_rows), (int)((l+1)*nb_rows), 0, WIDTH, std::ref(scene), low_left_corner, horizontal, vertical, origin, std::ref(img)};
}

  std::thread preview_thread {preview, WIDTH, HEIGHT, std::ref(img)};
  for(int l=0; l<NB_THREADS; l++){
    threads[l].join();
  }
 
  preview_thread.join();

  img.save_as("test.bmp");
  
  return 0;
}


