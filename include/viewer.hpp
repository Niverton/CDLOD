#pragma once

#include <GL/glew.h>      //glew need to be include before glfw
#include <GLFW/glfw3.h>
#include "terrain.hpp"
#include <string>

class Viewer{
  public:
    Viewer(int width, int height, const std::string& title);
    ~Viewer();

    void draw();

    bool shouldClose();
    void reshape(int width, int height);

    GLFWwindow* getGlfwWindow() { return window; }
  private:
    int width = 800;
    int height = 600;
    GLFWwindow* window = nullptr;

    Terrain terrain;
    Shader terrain_shader;
};
