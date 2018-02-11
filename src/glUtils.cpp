#include "glUtils.hpp"
#include <iostream>

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
}
