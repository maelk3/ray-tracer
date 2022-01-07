#include "sphere.h"
#include <cmath>

Sphere::Sphere(const vec3& center, const vec3& color, float radius) : center_(center), color_(color), radius_squared_(radius*radius) {}

const vec3& Sphere::center() const { return center_; }
const vec3& Sphere::color() const { return color_; }
float Sphere::radius_squared() const { return radius_squared_; }

bool Sphere::intersect(const Ray& ray) const {
  if(dot(ray.direction(), center_) < 0)
    return false;
  vec3 x = center_;
  vec3 a = ray.origin();
  vec3 b = ray.direction();
  vec3 x_hat = x-a;
  float dot_prod = dot(b, x_hat);
  float dist_squared = x_hat.norm_squared() - dot_prod*dot_prod/b.norm_squared();
  return dist_squared < radius_squared_;
}

vec3 Sphere::hit_point(const Ray& ray) const {
  vec3 oc = ray.origin()-center_;
  float a = ray.direction().norm_squared();
  float b = 2.0*dot(oc, ray.direction());
  float c = dot(oc, oc) - radius_squared_;
  float discriminant = b*b-4*a*c;
  float t = (-b - sqrt(discriminant))/(2.0*a);
  return ray.origin()+t*ray.direction();
}

std::ostream& operator<<(std::ostream& stream, const Sphere& sphere){
  return stream << "Sphere{center:" << sphere.center() << ", radius:" << sqrt(sphere.radius_squared()) << "}";
}
