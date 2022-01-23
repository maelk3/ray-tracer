#include "texture.h"
#include <cmath>

UniformTexture::UniformTexture(const vec3& color) : color(color) {}
vec3 UniformTexture::value(const vec3& pos) const {
  return color;
}

CheckerBoard::CheckerBoard(const vec3& color1, const vec3& color2, float stride) : color1(color1), color2(color2), stride(stride) {}
vec3 CheckerBoard::value(const vec3& pos) const {
  if((pos.x() - floor(pos.x()/(2.0*stride))*2.0*stride - stride)*(pos.y() - floor(pos.y()/(2.0*stride))*2.0*stride - stride)*(pos.z() - floor(pos.z()/(2.0*stride))*2.0*stride - stride) <= 0){
    return color1;
  }else{
    return color2;
  }
}
