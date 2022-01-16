#pragma once
#include "surface.h"
#include "vec.h"
#include <iostream>

class Sphere : public Surface {
  vec3 center_;
  float radius_;
 public:
  Sphere(const vec3& center, float radius, Material* mat);

  const vec3& center() const;
  float radius() const;

  bool hit(const Ray& ray, float t_min, float t_max, HitInfo& hit_info) const;
};

std::ostream& operator<<(std::ostream& stream, const Sphere& sphere);
