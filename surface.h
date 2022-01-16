#pragma once
#include "ray.h"

class Material;

struct HitInfo {
  float t;
  vec3 hit_point;
  vec3 normal;
  Material* mat;
};

class Material {
public:
  virtual bool scatter(const Ray& ray, const HitInfo& hit_info, vec3& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material {
public:
  Lambertian(const vec3& albedo);
  virtual bool scatter(const Ray& ray, const HitInfo& hit_info, vec3& attenuation, Ray& scattered) const;
  vec3 albedo;
};

class Metal : public Material {
public:
  Metal(const vec3& albedo, float fuzziness);
  virtual bool scatter(const Ray& ray, const HitInfo& hit_info, vec3& attenuation, Ray& scattered) const;
  vec3 albedo;
  float fuzziness;
};

class Solid : public Material {
public:
  virtual bool scatter(const Ray& ray, const HitInfo& hit_info, vec3& attenuation, Ray& scattered) const;
};

class Surface {
 public:
  Material* mat;
  Surface(Material* mat) : mat(mat) {}
  virtual bool hit(const Ray& ray, float t_min, float t_max, HitInfo& hit_info) const = 0;
};
