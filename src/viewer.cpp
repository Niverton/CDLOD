#include <iostream>
#include "viewer.hpp"

Viewer::Viewer(int width, int height, const std::string& title):
  width(width), height(height){
  
  window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!window){
    std::cerr << "Could not create GLFW window. :(\n";
    exit(-1);
  }

  glfwMakeContextCurrent(window);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LINE_SMOOTH);
}

Viewer::~Viewer(){
  glfwDestroyWindow(window);
}

void Viewer::draw(){
  // OpenGL code here;
}

void Viewer::reshape(int width, int height){
  this->width = width;
  this->height = height;

  glViewport(0, 0, width, height);
}

bool Viewer::shouldClose(){
  return glfwWindowShouldClose(window);
}
