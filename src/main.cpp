#include "viewer.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

[[noreturn]]
void usage(const char *cmd) {
  std::cerr << "Usage:\n" << cmd << ": <density (default=200)>\n";
  exit(1);
}

int main(int argc, char **argv) {
  unsigned int sphere_density = 200;
  if (argc > 1) {
    int sd;
    try {
      sd = std::stoi(argv[1]);
    } catch (const std::exception &e) {
      std::cerr << e.what() << '\n' << "";
      usage(argv[0]);
    }
    if (sd < 0) {
      std::cerr << "Density must be positive.\n";
      usage(argv[0]);
    }
    sphere_density = sd;
  }

  if (!glfwInit()) {
    std::cerr << "Could not initialize GLFW. :(\n";
    exit(-1);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  Viewer viewer(800, 600, "Projet de PDP", sphere_density);


  while (!viewer.shouldClose()) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    viewer.draw();

    glfwSwapBuffers(viewer.getGlfwWindow());
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
