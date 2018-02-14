#pragma once

#include "mesh.hpp"
#include "shader.hpp"

class Terrain : public Mesh {
public:
  Terrain(float sphere_radius, int sphere_density);
  ~Terrain();

  void draw(const Shader& shader);
};
