#include "list.h"

bool SurfaceList::hit(const Ray& ray, float t_min, float t_max, HitInfo& hit_info) const {
  HitInfo copy = hit_info;

  bool hit_anything = false;
  for(Surface* s : *this){
    if(s->hit(ray, t_min, t_max, copy)){
      hit_anything = true;
      if(copy.t <= hit_info.t){
	hit_info = copy;
      }
    }
  }
  
  return hit_anything;
}
