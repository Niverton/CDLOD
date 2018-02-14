#include "camera.hpp"

Camera::Camera(const glm::vec3& position, float fov, float aspect, float near, float far)
: position(position), fov(fov), aspect(aspect), near(near), far(far),
  transform(position, glm::vec3(), glm::vec3(1.0, 1.0, 1.0))
{

  projection_matrix = glm::perspective(fov, aspect, near, far);
  up = glm::vec3(0.0, 1.0, 0.0);
  right = glm::vec3(1.0, 0.0, 0.0);
}

void Camera::update(const Shader& shader){
  int mvp_location = shader.getUniformLocation("a_MVP");

  glUniformMatrix4fv(
    mvp_location,
    1,
    GL_FALSE,
    &transform.getMVP(getViewProjectionMatrix())[0][0]);
}
