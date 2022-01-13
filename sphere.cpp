#include "sphere.h"
#include <cmath>

Sphere::Sphere(const vec3& center, const vec3& color, float radius) : center_(center), color_(color), radius_(radius) {}

const vec3& Sphere::center() const { return center_; }
const vec3& Sphere::color() const { return color_; }
float Sphere::radius() const { return radius_; }

bool Sphere::hit(const Ray& ray, float t_min, float t_max, HitInfo& hit_info) const {
  vec3 oc = ray.origin()-center_;
  float a = ray.direction().norm_squared();
  float b = 2.0*dot(oc, ray.direction());
  float c = dot(oc, oc) - radius_*radius_;
  float discriminant = b*b-4*a*c;

  if(discriminant >= 0.0 && dot(ray.direction(), center_) >= 0.0){
    hit_info.t = (-b - sqrt(discriminant))/(2.0*a);
    hit_info.normal = (ray.origin()+hit_info.t*ray.direction()-center_).normalize();
    hit_info.color = 0.5*(hit_info.normal + vec3(1.0, 1.0, 1.0));
    return true;
  }else{
    return false;
  }
}

std::ostream& operator<<(std::ostream& stream, const Sphere& sphere){
  return stream << "Sphere{center:" << sphere.center() << ", radius:" << sphere.radius() << "}";
}
