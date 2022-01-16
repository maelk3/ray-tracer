#include "preview.h"
#include "shader.h"
#include <GL/glew.h>
#include <GL/freeglut.h>

static GLuint VAO;
static GLuint VBO;

static void init(int width, int height, Image& img){

  const GLubyte tex_data[] = {
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
    0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF
  };
    
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
    {GL_VERTEX_SHADER, "./texture.vert"},
    {GL_FRAGMENT_SHADER, "./texture.frag"}
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
}

static void display(){
  glClear(GL_COLOR_BUFFER_BIT);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBindVertexArray(VAO);

  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
  
  glFlush();

  glutPostRedisplay();
}

void preview(int width, int height, Image& img){

  int argc = 0;
  glutInit(&argc, nullptr);
  glutInitDisplayMode(GLUT_RGBA);
  glutInitWindowSize(width, height);
  glutInitContextVersion(4, 3);
  glutInitContextProfile(GLUT_CORE_PROFILE);
  glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
  glutInitDisplayMode(GLUT_RGBA);
  glutInitWindowSize(800, 600);
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
  
  glutMainLoop();
}
