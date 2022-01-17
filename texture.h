#pragma once
#include "vec.h"

class Texture {
 public:
  virtual vec3 value(const vec3& pos) const = 0;
};

class UniformTexture : public Texture {
  vec3 color;
 public:
  UniformTexture(const vec3& color);
  virtual vec3 value(const vec3& pos) const;
};

class CheckerBoard : public Texture {
  vec3 color1, color2;
  float stride;
 public:
  CheckerBoard(const vec3& color1, const vec3& color2, float stride);
  virtual vec3 value(const vec3& pos) const;
};

