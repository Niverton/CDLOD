#pragma once

#include <glm/glm.hpp>

class Camera{
public:
  Camera();
  ~Camera();

  void lookAt(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up);
  glm::mat4 projectionMatrix() const;

  /*!
      \return projection * view * model matrix.
      /!\ the order of multiplications is important.
  */
  glm::mat4 getMPV() const;

protected:
  glm::vec3 position;
  glm::vec3 target;
  glm::mat4 view_matrix;
  glm::mat4 model_matrix;
  float fov = 90.0f;
  float near = 0.01f;
  float far = 100000.0f;
  float ratio = 4.0f / 3.0f;
};
