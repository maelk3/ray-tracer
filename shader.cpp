#include "shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

char* copy_string(const std::string& str){
  char* res = new char[str.length()+1];
  for(int i=0; i<str.length(); i++)
    res[i] = str[i];
  res[str.length()] = 0;

  return res;
}

char* read_file(const std::string& file_path){
  std::ifstream file(file_path);
  std::stringstream strstream;
  strstream << file.rdbuf();
  std::string str = strstream.str();

  return copy_string(str);
}

GLuint compile_shaders(const Shader_info* shader_info, int nb_shaders){
  GLuint* shaders = new GLuint[nb_shaders];
  GLint status;

  for(int i=0; i<nb_shaders; i++){
    shaders[i] = glCreateShader(shader_info[i].type);

    GLchar* source[1] = {nullptr};
    source[0] = read_file(shader_info[i].path);
    glShaderSource(shaders[i], 1, source, NULL);
    glCompileShader(shaders[i]);
    
    glGetShaderiv(shaders[i], GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE){
      GLint log_length;
      glGetShaderiv(shaders[i], GL_INFO_LOG_LENGTH, &log_length);

      GLchar* log_info = new GLchar[log_length];
      glGetShaderInfoLog(shaders[i], log_length, &log_length, log_info);
      std::cerr << log_info;
    }
  }

  GLuint program = glCreateProgram();
  for(int i=0; i<nb_shaders; i++)
    glAttachShader(program,  shaders[i]);

  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if(status != GL_TRUE){
    GLint log_length;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);

    GLchar* log_info = new GLchar[log_length];
    glGetProgramInfoLog(program, log_length, &log_length, log_info);
    std::cerr << log_info;
  }
  
  return program;
}
