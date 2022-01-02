#pragma once
#include <string>

struct Color {
  unsigned char r, g, b;
};

class Image {
  int width, height;
  Color* image_data;

 public:
  Image(int w, int h);
  ~Image();

  Color& operator()(int i, int j);
  const Color& operator()(int i, int j) const;

  void save_as(const std::string& file_path);
  static Image load(const std::string& file_path);
};
