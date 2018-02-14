#include "transform.hpp"
#include <glm/gtx/transform.hpp>


Transform::Transform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& sca)
: position(pos), rotation(rot), scale(sca){}

glm::mat4 Transform::getModel(){
  glm::mat4 position_matrix = glm::translate(position);
  glm::mat4 rotX = glm::rotate(rotation.x, glm::vec3(1.0, 0.0, 0.0));
  glm::mat4 rotY = glm::rotate(rotation.y, glm::vec3(0.0, 1.0, 0.0));
  glm::mat4 rotZ = glm::rotate(rotation.z, glm::vec3(0.0, 0.0, 1.0));
  glm::mat4 rotation_matrix = rotX * rotY * rotZ;
  glm::mat4 scale_matrix = glm::scale(scale);
  
  return position_matrix * rotation_matrix * scale_matrix;
}

glm::mat4 Transform::getMVP(glm::mat4 viewProjectionMatrix){
  glm::mat4 view_projection_matrix = viewProjectionMatrix;
	glm::mat4 model = getModel();

  return view_projection_matrix * model;
}

glm::vec3 Transform::getPosition(){
  return position;
}

void Transform::setPosition(const glm::vec3& pos){
  this->position = position;
}

glm::vec3 Transform::getRotation(){
  return rotation;
}

void Transform::setRotation(const glm::vec3& rotation){
  this->rotation = rotation;
}

glm::vec3 Transform::getScale(){
  return scale;
}

void Transform::setScale(const glm::vec3& scale){
  this->scale = scale;
}

