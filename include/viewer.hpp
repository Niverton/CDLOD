#pragma once

#include "terrain.hpp"
#include <GL/glew.h> //glew need to be include before glfw
#include <GLFW/glfw3.h>
#include <memory>
#include <string>
#include "camera.hpp"

class Viewer {
public:
  Viewer(int width, int height, const std::string &title, int sphere_density);
  ~Viewer();

  void draw();

  bool shouldClose();
  void reshape(int width, int height);

  GLFWwindow *getGlfwWindow() {
    return window;
  }

  Camera* getCamera(){
    return camera.get();
  }
private:
  int width = 800;
  int height = 600;
  GLFWwindow *window = nullptr;

  std::shared_ptr<Camera> camera;
  std::unique_ptr<Terrain> terrain;
  std::unique_ptr<Shader> terrain_shader;

  static void key_callback(GLFWwindow *window, int key, int scancode, 
    int action, int mods);

};
