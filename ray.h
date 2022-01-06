#pragma once
#include "vec.h"
#include <iostream>

class Ray {
  vec3 origin_, direction_;
 public:
  template<typename T, typename U>
    Ray(T&& origin, U&& direction) : origin_(std::forward<T>(origin)), direction_(std::forward<U>(direction)){}
  
  const vec3& origin() const;
  const vec3& direction() const;
  
  vec3 point_at(float t) const;
};

std::ostream& operator<<(std::ostream& stream, const Ray& ray);
