#pragma once
#include "mesh.hpp"
#include "shader.hpp"

class Terrain : public Mesh{
public:
  Terrain();
  ~Terrain();

  void draw();
  
private:
  Shader shader;
};
