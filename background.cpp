#include "background.h"

bool BackgroundGradient::hit(const Ray& ray, float t_min, float t_max, HitInfo& hit_info) const {
  vec3 dir = unit_vector(ray.direction());
  float t = 0.5*(dir.y()+1.0);
  hit_info.t = std::numeric_limits<float>::max();
  hit_info.color = (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
  return true;
}
