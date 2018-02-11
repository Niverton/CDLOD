#pragma once

#include <glm/glm.hpp>
#include <ostream>
#include <vector>

class SphereMesh {
  friend void SpherifiedCube(uint32_t, SphereMesh &);
  friend std::ostream &operator<<(std::ostream &o, const SphereMesh &mesh);

public:
  SphereMesh(int radius_, int density);
  std::ostream &operator<<(std::ostream &o);

private:
  void Generate(int density);

  int addVertex(glm::vec3 v);
  void addQuad(int a, int b, int c, int d);
  void addQuadAlt(int a, int b, int c, int d);

  int radius;

  std::vector<glm::vec3> vertices;
  std::vector<glm::vec3> faces;
};
