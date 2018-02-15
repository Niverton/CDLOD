#include "viewer.hpp"
#include "glUtils.hpp"
#include <iostream>

Viewer::Viewer(int width, int height, const std::string &title,
               int sphere_density)
    : width(width), height(height) {

  window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!window) {
    std::cerr << "Could not create GLFW window. :(\n";
    exit(-1);
  }

  glfwMakeContextCurrent(window);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfwSetWindowUserPointer(getGlfwWindow(), this);
  glfwSetKeyCallback(getGlfwWindow(), key_callback);
  glUtils::initGL();

  reshape(width, height);
  glFrontFace(GL_CW);
  glCullFace(GL_FRONT_AND_BACK);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LINE_SMOOTH);

  reshape(width, height);
  try {
    terrain = std::make_unique<Terrain>(-0.25f, sphere_density);
  } catch (std::string &exception) {
    std::cerr << exception;
    exit(-1);
  }
  terrain_shader = std::make_unique<Shader>();
  bool vert_status, frag_status, link_status;
  vert_status = terrain_shader->loadFromFile("shaders/terrain.vert", Shader::Type::VERTEX);
  frag_status = terrain_shader->loadFromFile("shaders/terrain.frag", Shader::Type::FRAGMENT);
  link_status = terrain_shader->link();
  
  if (!vert_status || !frag_status || !link_status){
     throw "Error: could not create shader.";
  }

  glm::vec3 cam_position = glm::vec3(-5.0, 0.0, -2.0);
  glm::vec3 cam_target = glm::vec3(0.0, 2.0, 0.0);
  camera = std::make_shared<Camera>(
    cam_position, 
    cam_target,
    70.0f, 
    static_cast<float>(width) / static_cast<float>(height), 
    0.1f, 
    1000.0f);
}

Viewer::~Viewer() {
  glfwDestroyWindow(window);
}

void Viewer::draw() {
  /*Get all matrix*/
  glm::mat4 model_matrix = terrain->getModelMatrix();
  glm::mat4 camera_matrix = camera->getCameraMatrix();
  glm::mat4 projection_matrix = camera->getProjectionMatrix();

  glm::mat4 mvp = projection_matrix * camera_matrix * model_matrix;


  terrain_shader->activate();  
  //Send mvp matrix to gc
  int mvp_location = terrain_shader->getUniformLocation("a_MVP");
  glUniformMatrix4fv(mvp_location, 1, GL_FALSE, &mvp[0][0]);


  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glDepthFunc(GL_LESS);
  terrain->draw(*terrain_shader);
  terrain_shader->deactivate();
}

void Viewer::reshape(int width, int height) {
  this->width = width;
  this->height = height;

  glViewport(0, 0, width, height);
}

bool Viewer::shouldClose() {
  return glfwWindowShouldClose(window);
}



void Viewer::key_callback(GLFWwindow *window, int key, int scancode, int action,
    int mods) {

  void* ptr_viewer = glfwGetWindowUserPointer(window);
  Viewer* viewer = static_cast<Viewer*>(ptr_viewer);
  Camera* camera = viewer->getCamera();

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
  
  if (action == GLFW_PRESS || action == GLFW_REPEAT){
    switch(key){
    case GLFW_KEY_UP:   //forward
      camera->setPosition(camera->getPosition() + glm::vec3(0.0, 0.0, 1.0));
      break;
    case GLFW_KEY_DOWN:
      camera->setPosition(camera->getPosition() + glm::vec3(0.0, 0.0, -1.0));
      break;
    case GLFW_KEY_LEFT:
      camera->setPosition(camera->getPosition() + glm::vec3(-.0, -1.0, 0.0));
      break;
    case GLFW_KEY_RIGHT:
      camera->setPosition(camera->getPosition() + glm::vec3(0.0, 1.0, 1.0));
      break;
    
    }
  }
}
