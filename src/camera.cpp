#include "camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
: model_matrix(glm::mat4(1.0f)) //set model matrix as identity
{
}

Camera::~Camera(){

}

void Camera::lookAt(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up){
  view_matrix = glm::lookAt(position, target, up);
}

glm::mat4 Camera::projectionMatrix() const {
  return glm::perspective(glm::radians(fov), ratio, near, far);
}
