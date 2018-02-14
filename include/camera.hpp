#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "transform.hpp"
#include "shader.hpp"

class Camera{
public:
  Camera(const glm::vec3& position, const glm::vec3& target,
          float fov, float aspect, float near, float far);

  ~Camera() {};

  glm::mat4 getCameraMatrix(){
    return glm::lookAt(position, target, glm::vec3(0.0, 1.0, 0.0));
  }

  glm::mat4 getProjectionMatrix(){
    return projection_matrix;
  }

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
};
