#include "camera.hpp"
#include <iostream>

Camera::Camera(const glm::vec3& position, const glm::vec3& target,
                float fov, float aspect, float near, float far)
: position(position), target(target),  fov(fov), aspect(aspect), near(near), far(far)
{

  projection_matrix = glm::perspective(fov, aspect, near, far);
  up = glm::vec3(0.0, 1.0, 0.0);
  right = glm::vec3(1.0, 0.0, 0.0);
}

