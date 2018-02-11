#include <iostream>
#include "viewer.hpp"
#include "glUtils.hpp"
#include "terrain.hpp"

Viewer::Viewer(int width, int height, const std::string& title):
  width(width), height(height){
  
  window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!window){
    std::cerr << "Could not create GLFW window. :(\n";
    exit(-1);
  }

  glfwMakeContextCurrent(window);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glUtils::initGL();

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LINE_SMOOTH);


  terrain = new Terrain();
  terrain_shader = new Shader();

  terrain_shader->loadFromFile("shaders/terrain.vert", Shader::Type::VERTEX);
  terrain_shader->loadFromFile("shaders/terrain.frag", Shader::Type::FRAGMENT);
}

Viewer::~Viewer(){
  glfwDestroyWindow(window);
}

void Viewer::draw(){
  terrain_shader->activate();
  terrain->draw(*terrain_shader);
  terrain_shader->deactivate();
}

void Viewer::reshape(int width, int height){
  this->width = width;
  this->height = height;

  glViewport(0, 0, width, height);
}

bool Viewer::shouldClose(){
  return glfwWindowShouldClose(window);
}
