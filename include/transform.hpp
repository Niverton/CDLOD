#pragma once

#include <glm/glm.hpp>

class Transform{
public:
  Transform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& sca);

  glm::mat4 getModel();
  glm::mat4 getMVP(glm::mat4 viewPorjectionMatrix);
  
  glm::vec3 getPosition();
  void setPosition(const glm::vec3& pos);

  glm::vec3 getRotation();
  void setRotation(const glm::vec3& rotation);

  glm::vec3 getScale();
  void setScale(const glm::vec3& scale);

  ~Transform() {}
private:
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;
};
