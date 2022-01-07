#pragma once
#include "surface.h"
#include "vec.h"
#include <iostream>

class Sphere : public Surface {
  vec3 center_;
  vec3 color_;
  float radius_;
 public:
  Sphere(const vec3& center, const vec3& color, float radius);

  const vec3& center() const;
  const vec3& color() const;
  float radius() const;

  bool hit(const Ray& ray, float t_min, float t_max, HitInfo& hit_info) const;
};

std::ostream& operator<<(std::ostream& stream, const Sphere& sphere);
