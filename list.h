#pragma once
#include "surface.h"
#include <vector>

class SurfaceList : public Surface, public std::vector<Surface*> {
 public:
  SurfaceList() : std::vector<Surface*>(), Surface() {}
  bool hit(const Ray& ray, float t_min, float t_max, HitInfo& hit_info) const;
};
