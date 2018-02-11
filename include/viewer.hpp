#pragma once

#include <GL/glew.h>      //glew need to be include before glfw
#include <GLFW/glfw3.h>
#include "terrain.hpp"
#include <string>
#include <memory>

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

    std::unique_ptr<Terrain> terrain;
    std::unique_ptr<Shader> terrain_shader;
};
