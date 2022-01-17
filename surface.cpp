#include "surface.h"
#include <limits>

Lambertian::Lambertian(Texture* albedo) : albedo(albedo) {}
bool Lambertian::scatter(const Ray& ray, const HitInfo& hit_info, vec3& attenuation, Ray& scattered) const {
  vec3 target = hit_info.hit_point + hit_info.normal + get_random_unit();
  scattered = Ray(hit_info.hit_point, unit_vector(target-hit_info.hit_point));
  attenuation = albedo->value(hit_info.hit_point);
  return true;
}



Metal::Metal(Texture* albedo, float fuzziness) : albedo(albedo), fuzziness(fuzziness) {}
bool Metal::scatter(const Ray& ray, const HitInfo& hit_info, vec3& attenuation, Ray& scattered) const {
  vec3 direction = unit_vector(ray.direction());
  vec3 reflected = direction - 2.0*dot(direction, hit_info.normal)*hit_info.normal;
  scattered = Ray(hit_info.hit_point, reflected + fuzziness*get_random_unit());
  attenuation = albedo->value(hit_info.hit_point);
  return (dot(scattered.direction(), hit_info.normal) > 0);
}

bool Solid::scatter(const Ray& ray, const HitInfo& hit_info, vec3& attenuation, Ray& scattered) const {
  return false;
}
