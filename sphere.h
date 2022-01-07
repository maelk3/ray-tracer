#pragma once
#include "vec.h"
#include "ray.h"
#include <iostream>

class Sphere {
  vec3 center_;
  vec3 color_;
  float radius_squared_;
 public:
  Sphere(const vec3& center, const vec3& color, float radius);

  const vec3& center() const;
  const vec3& color() const;
  float radius_squared() const;

  bool intersect(const Ray& ray) const;
  vec3 hit_point(const Ray& ray) const;
};

std::ostream& operator<<(std::ostream& stream, const Sphere& sphere);
