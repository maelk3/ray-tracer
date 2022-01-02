#include "image.h"
#include <fstream>
#include <algorithm>
#include <iterator>

Image::Image(int w, int h) : width(w), height(h), image_data(new Color[width*height]) {}

Image::~Image(){
  delete[] image_data;
}

Color& Image::operator()(int i, int j){
  return image_data[i*width+j];
}

const Color& Image::operator()(int i, int j) const {
  return image_data[i*width+j];
}

void Image::save_as(const std::string& file_path){

  std::ofstream file_stream(file_path, std::ios_base::binary);
  if(!file_stream){
    throw "the file could not be opened";
  }

  std::ostream_iterator<char> it(file_stream);

  file_stream << "BM";
  uint32_t file_header[3] = {(uint32_t)54+3*width*height, 0, 54};

  std::copy((char*)file_header, (char*)&file_header[3], it);

  uint32_t bitmap_header[10] = {
    40,
    (uint32_t)width,
    (uint32_t)height,
    (24 << 16) | 1,
    0,
    (uint32_t)3*width*height,
    0x130B,
    0x130B,
    0,
    0
  };

  std::copy((char*)bitmap_header, (char*)&bitmap_header[10], it);

  std::copy((char*)image_data, (char*)&image_data[width*height], it);
}

