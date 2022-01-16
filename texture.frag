#version 430 core

uniform sampler2D tex;

in vec2 out_tex_coord;
out vec4 fColor;

void main(){
    fColor = texture(tex, out_tex_coord);
}

