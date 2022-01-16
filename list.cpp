#include "list.h"
#include <limits>

bool SurfaceList::hit(const Ray& ray, float t_min, float t_max, HitInfo& hit_info) const {
  HitInfo temp_hit_info;

  bool hit_anything = false;
  float closest = std::numeric_limits<float>::max();
  for(Surface* s : *this){
    if(s->hit(ray, t_min, t_max, temp_hit_info)){
      if(temp_hit_info.t <= closest){
	hit_anything = true;	
	hit_info = temp_hit_info;
	closest = temp_hit_info.t;
      }
    }
  }
  
  return hit_anything;
}
