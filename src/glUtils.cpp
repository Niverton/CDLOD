#include "glUtils.hpp"
#include <iostream>
#include <string>

void glUtils::initGL(){
  glewExperimental=true;
  GLenum status = glewInit();
  if (status != GLEW_OK){
    std::cerr << "Error: could not initialize GLEW: " << glewGetErrorString(status) << ". :(\n";
    exit(-1);
  }
  std::cout << "Using GLEW " << glewGetString(GLEW_VERSION) << ".\n";

  if (!glewIsSupported("GL_VERSION_3_3")){
    std::cerr << "Error: OpenGL 3.3 is not suported by your system. :(\n";
    exit(-1);
  }

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback( (GLDEBUGPROC) callback_error, 0);
}


void glUtils::callback_error(
  GLenum src, 
  GLenum type, 
  GLuint id, 
  GLenum severity,
  GLsizei length,
  const GLchar* message,
  const void* userParam){
  if (type == GL_DEBUG_TYPE_ERROR){
    std::cerr << "GL ERROR -" << " id: " << id << 
    " severity: " << severity << '\t' << "msg: " << (void*) message << '\n';
  }
}
