#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "transform.hpp"
#include "shader.hpp"

class Camera{
public:
  Camera(const glm::vec3& position, float fov, float aspect, float near, float far);
  ~Camera() {};

  glm::mat4 getViewProjectionMatrix() const{
    return projection_matrix * glm::lookAt(position, position + glm::vec3(0.0, 0.0, 1.0), up);
  }
  
  void update(const Shader& shader);

protected:
  glm::vec3 position;
  glm::vec3 target;
  glm::mat4 projection_matrix;
  glm::mat4 model_matrix;

  glm::vec3 up;
  glm::vec3 right;

  float near;
  float far;
  float fov;
  float aspect;
  Transform transform;
};
