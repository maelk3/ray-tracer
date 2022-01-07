#pragma once
#include "ray.h"

struct HitInfo {
  float t;
  vec3 p;
  vec3 normal;
};

class Surface {
 public:
  virtual bool hit(const Ray& ray, float t_min, float t_max, HitInfo& hit_info) const = 0;
};
