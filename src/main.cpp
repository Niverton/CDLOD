#include <iostream>

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "viewer.hpp"

namespace callback{
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    switch (key){
      case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        break;

      default:
        break;
    }
  }

  void error_callback(int error, const char* des){
    std::cerr << "Error: " << error << " " << des << '\n';
  }
}

int main(int argc, char **argv) {
  
  if (!glfwInit()){
    std::cerr << "Could not initialize GLFW. :(\n";
    exit(-1);
  }

  Viewer viewer(800, 600, "PDP");
  glfwSetKeyCallback(viewer.getGlfwWindow(), callback::key_callback);
  glfwSetErrorCallback(callback::error_callback);
  


  while(!viewer.shouldClose()){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.2f, 0.5f, 1.0f);
    viewer.draw();

    glfwSwapBuffers(viewer.getGlfwWindow());
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
