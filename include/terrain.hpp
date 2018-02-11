#pragma once
#include "mesh.hpp"

class Terrain : public Mesh{
public:
  Terrain();
  ~Terrain();

  void draw(const Shader& shader);
};
