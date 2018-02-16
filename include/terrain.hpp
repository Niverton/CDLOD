#pragma once

#include "mesh.hpp"
#include "shader.hpp"

class Terrain : public Mesh {
public:
  Terrain(float sphere_radius, int sphere_density);
  ~Terrain();

  void draw(const Shader& shader);
  glm::mat4 getModelMatrix(){
    return glm::mat4(1.0);
  }
};
