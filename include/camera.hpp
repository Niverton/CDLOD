#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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

  glm::vec3 getPosition() { return position; }
  void setPosition(const glm::vec3& position){
    this->position = position;
  }

  glm::vec3 getTarget() { return target; }
  void setTarget(const glm::vec3& target){
    this->position = target;
  }

  float getFov(){ return fov; }
  void setFov(float fov){
    this->fov = fov;
  }

  float getNear(){ return near; }
  void setNear(float near){
    this->near = near;
  } 

  float getFar(){ return near; }
  void setFar(float near){
    this->far = far;
  } 


  float getAspect(){ return near; }
  void setAscpect(float ascpect){
    this->aspect = aspect;
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
