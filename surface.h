#pragma once
#include "ray.h"
#include <limits>

enum class Material {Diffuse, Solid};

class HitInfo {
public:
  HitInfo() : t(std::numeric_limits<float>::max()) {}
  float t;
  vec3 color;
  vec3 normal;
  Material mat;
};

class Surface {
 public:
  Material mat;
  Surface(Material mat) : mat(mat) {}
  Surface() : mat(Material::Solid) {}
  virtual bool hit(const Ray& ray, float t_min, float t_max, HitInfo& hit_info) const = 0;
};
