#version 430 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec2 tex_coord;

uniform float window_aspect_ratio;
uniform float image_aspect_ratio;

out vec2 out_tex_coord;

void main(){
  float ratio = window_aspect_ratio/image_aspect_ratio;
  if(ratio > 1){
    gl_Position = vec4(vPosition.x/ratio, vPosition.yzw);
  }else{
    gl_Position = vec4(vPosition.x, vPosition.y*ratio, vPosition.zw);
  }
  
  out_tex_coord = tex_coord;
}

