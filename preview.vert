#version 430 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 tex_coord;

out vec2 out_tex_coord;

void main(){
  gl_Position = vPosition;
  out_tex_coord = tex_coord;
}

