#pragma once

#include <string>
#include <GL/glew.h>

struct Shader_info {
  int type;
  std::string path;
};

GLuint compile_shaders(const Shader_info* shader_info, int nb_shaders);
