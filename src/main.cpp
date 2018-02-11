#include <iostream>

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "viewer.hpp"

namespace input{
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    std::cout << key << '\n';
    switch (key){
      case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        break;

      default:
        break;
    }
  }
}

int main(int argc, char **argv) {
  
  if (!glfwInit()){
    std::cerr << "Could not initialize GLFW. :(\n";
    exit(-1);
  }

  Viewer viewer(800, 600, "PDP");
  glfwSetKeyCallback(viewer.getGlfwWindow(), input::key_callback);

  


  while(!viewer.shouldClose()){
    
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
