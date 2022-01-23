#include "preview.h"
#include "shader.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <thread>
#include <chrono>

static GLuint VAO;
static GLuint VBO;

static GLint window_aspect_ratio;
static GLint image_aspect_ratio;

static Image* img_;
static int width_, height_;

static void init(int width, int height, Image& img){
    
  const GLfloat quad_data[] = {
    -1.0f, -1.0f, 0.0f, 1.0f,
    1.0f,  -1.0f, 0.0f, 1.0f,
    1.0f,   1.0f, 0.0f, 1.0f,
    -1.0f,  1.0f, 0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f
  };

  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glActiveTexture(GL_TEXTURE0 + 0);

  GLuint sampler;  
  glGenSamplers(1, &sampler);
  glBindSampler(0, sampler);
  glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexStorage2D(GL_TEXTURE_2D, 4, GL_RGB8, width, height);
  glTexSubImage2D(GL_TEXTURE_2D,
		  0,
		  0, 0,
		  width, height,
		  GL_RGB, GL_UNSIGNED_BYTE,
		  img.image_data);
  
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quad_data), quad_data, GL_STATIC_DRAW);

  Shader_info shaders[2] = {
    {GL_VERTEX_SHADER, "./preview.vert"},
    {GL_FRAGMENT_SHADER, "./preview.frag"}
  };
    
  GLuint program = compile_shaders(shaders, 2);
  glUseProgram(program);
  
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  GLint sampler_attribute = glGetUniformLocation(program, "tex");
  glUniform1i(sampler_attribute, 0);

  GLint vertex_position = glGetAttribLocation(program, "vPosition");
  glVertexAttribPointer(vertex_position, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
  glEnableVertexAttribArray(vertex_position);

  GLint texture_coord = glGetAttribLocation(program, "tex_coord");
  glVertexAttribPointer(texture_coord, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(16*sizeof(float)));
  glEnableVertexAttribArray(texture_coord);

  window_aspect_ratio = glGetUniformLocation(program, "window_aspect_ratio");
  image_aspect_ratio = glGetUniformLocation(program, "image_aspect_ratio");
  glUniform1f(image_aspect_ratio, (float)width_/(float)height_);
}

static void display(){
  glClear(GL_COLOR_BUFFER_BIT);

  glTexSubImage2D(GL_TEXTURE_2D,
		  0,
		  0, 0,
		  width_, height_,
		  GL_RGB, GL_UNSIGNED_BYTE,
		  img_->image_data);
   
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBindVertexArray(VAO);

  int curr_window_width = glutGet(GLUT_WINDOW_WIDTH);
  int curr_window_height = glutGet(GLUT_WINDOW_HEIGHT);
  glUniform1f(window_aspect_ratio, (float)curr_window_width/(float)curr_window_height);

  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
  
  glutSwapBuffers();

  glutPostRedisplay();
}

void preview(int width, int height, Image& img){

  width_ = width;
  height_ = height;
  img_ = &img;
  
  int argc = 0;
  glutInit(&argc, nullptr);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowSize(width, height);
  glutInitContextVersion(4, 3);
  glutInitContextProfile(GLUT_CORE_PROFILE);
  glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
  glutInitDisplayMode(GLUT_RGBA);
  glutInitContextVersion(4, 3);
  glutInitContextProfile(GLUT_CORE_PROFILE);
  glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

  int window_id = glutCreateWindow("preview");

  if(glewInit()){
    std::cerr << "Unable toinit ialize GLEW ... exiting" << std::endl;
    exit(EXIT_FAILURE);
  }

  init(width, height, img);

  glutDisplayFunc(display);

  int curr_window_width = glutGet(GLUT_WINDOW_WIDTH);
  int curr_window_height = glutGet(GLUT_WINDOW_HEIGHT);

  std::cout << curr_window_width << "," << curr_window_height << std::endl;
  
  glutMainLoop();
}
