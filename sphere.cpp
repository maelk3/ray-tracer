#include "sphere.h"
#include <cmath>

Sphere::Sphere(const vec3& center, float radius, Material* mat) : center_(center), radius_(radius), Surface(mat) {}

const vec3& Sphere::center() const { return center_; }
float Sphere::radius() const { return radius_; }

bool Sphere::hit(const Ray& ray, float t_min, float t_max, HitInfo& hit_info) const {
  vec3 oc = ray.origin()-center_;
  float a = ray.direction().norm_squared();
  float b = 2.0*dot(oc, ray.direction());
  float c = dot(oc, oc) - radius_*radius_;
  float discriminant = b*b-4*a*c;
  float t = (-b - sqrt(discriminant))/(2.0*a);

  if(discriminant >= 0.0 && dot(ray.direction(), center_) >= 0.0 && (t_min <= t) && (t <= t_max)){
    hit_info.t = t;
    hit_info.hit_point = ray.origin() + t*ray.direction();
    hit_info.normal = (hit_info.hit_point-center_).normalize();
    hit_info.mat = this->mat;
    return true;
  }else{
    return false;
  }
}

std::ostream& operator<<(std::ostream& stream, const Sphere& sphere){
  return stream << "Sphere{center:" << sphere.center() << ", radius:" << sphere.radius() << "}";
}
