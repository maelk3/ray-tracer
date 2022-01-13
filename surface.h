#pragma once
#include "ray.h"
#include <limits>

class HitInfo {
public:
  HitInfo() : t(std::numeric_limits<float>::max()) {}
  float t;
  vec3 color;
  vec3 normal;
};

class Surface {
 public:
  virtual bool hit(const Ray& ray, float t_min, float t_max, HitInfo& hit_info) const = 0;
};
