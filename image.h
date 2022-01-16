#pragma once
#include <string>
#include "vec.h"

class Color {
public:
  Color() = default;
  Color(const vec3& col);
  Color& operator=(const vec3& col);
  unsigned char r, g, b;
};

class Image {
  int width, height;
 public:
  Color* image_data;
  Image(int w, int h);
  ~Image();

  Color& operator()(int i, int j);
  const Color& operator()(int i, int j) const;

  void save_as(const std::string& file_path);
  static Image load(const std::string& file_path);
};
