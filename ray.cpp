#include "ray.h"

const vec3& Ray::origin() const { return origin_; }
const vec3& Ray::direction() const { return direction_; }

vec3 Ray::point_at(float t) const {
  return origin_ + t*direction_;
}

std::ostream& operator<<(std::ostream& stream, const Ray& ray){
  stream << "Ray{origin:" << ray.origin() << ",direction:" << ray.direction() << "}";
  return stream;
}
