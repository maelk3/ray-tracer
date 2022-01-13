#pragma once
#include "surface.h"
#include <limits>

class BackgroundGradient : public Surface {
 public:
  bool  hit(const Ray& ray, float t_min, float t_max, HitInfo& hit_info) const;
};
