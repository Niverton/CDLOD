#include "sphere_mesh.hpp"

#include <glm/gtc/noise.hpp>

// ---------------------------------- EXTERN ----------------------------------
/* Taken from https://github.com/caosdoar/spheres
 * License:
 *
 * MIT License
 * Copyright (c) 2015 Oscar Sebio Cajaraville
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software. THE SOFTWARE IS PROVIDED
 * "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

using namespace type;

namespace CubeToSphere {
static const Vec3 origins[6] = {Vec3(-1.0, -1.0, -1.0), Vec3(1.0, -1.0, -1.0),
                                Vec3(1.0, -1.0, 1.0),   Vec3(-1.0, -1.0, 1.0),
                                Vec3(-1.0, 1.0, -1.0),  Vec3(-1.0, -1.0, 1.0)};
static const Vec3 rights[6] = {Vec3(2.0, 0.0, 0.0),  Vec3(0.0, 0.0, 2.0),
                               Vec3(-2.0, 0.0, 0.0), Vec3(0.0, 0.0, -2.0),
                               Vec3(2.0, 0.0, 0.0),  Vec3(2.0, 0.0, 0.0)};
static const Vec3 ups[6] = {Vec3(0.0, 2.0, 0.0), Vec3(0.0, 2.0, 0.0),
                            Vec3(0.0, 2.0, 0.0), Vec3(0.0, 2.0, 0.0),
                            Vec3(0.0, 0.0, 2.0), Vec3(0.0, 0.0, -2.0)};
}; // namespace CubeToSphere

void SpherifiedCube(uint32_t divisions, SphereMesh &mesh) {
  const double step = 1.0 / double(divisions);
  const Vec3 step3(step, step, step);

  for (uint32_t face = 0; face < 6; ++face) {
    const Vec3 origin = CubeToSphere::origins[face];
    const Vec3 right = CubeToSphere::rights[face];
    const Vec3 up = CubeToSphere::ups[face];
    for (uint32_t j = 0; j < divisions + 1; ++j) {
      const Vec3 j3(j, j, j);
      for (uint32_t i = 0; i < divisions + 1; ++i) {
        const Vec3 i3(i, i, i);
        const Vec3 p = origin + step3 * (i3 * right + j3 * up);
        const Vec3 p2 = p * p;
        const Vec3 n(
            p.x * std::sqrt(1.0 - 0.5 * (p2.y + p2.z) + p2.y * p2.z / 3.0),
            p.y * std::sqrt(1.0 - 0.5 * (p2.z + p2.x) + p2.z * p2.x / 3.0),
            p.z * std::sqrt(1.0 - 0.5 * (p2.x + p2.y) + p2.x * p2.y / 3.0));
        mesh.addVertex(n);
      }
    }
  }

  const uint32_t k = divisions + 1;
  for (uint32_t face = 0; face < 6; ++face) {
    for (uint32_t j = 0; j < divisions; ++j) {
      const bool bottom = j < (divisions / 2);
      for (uint32_t i = 0; i < divisions; ++i) {
        const bool left = i < (divisions / 2);
        const uint32_t a = (face * k + j) * k + i;
        const uint32_t b = (face * k + j) * k + i + 1;
        const uint32_t c = (face * k + j + 1) * k + i;
        const uint32_t d = (face * k + j + 1) * k + i + 1;
        if (bottom ^ left)
          mesh.addQuadAlt(a, c, d, b);
        else
          mesh.addQuad(a, c, d, b);
      }
    }
  }
}

void SphereMesh::addQuad(int a, int b, int c, int d) {
  faces.emplace_back(Vec3{a, b, c});
  faces.emplace_back(Vec3{a, c, d});
}

void SphereMesh::addQuadAlt(int a, int b, int c, int d) {
  faces.emplace_back(Vec3{a, b, d});
  faces.emplace_back(Vec3{b, c, d});
}

// -------------------------------- END EXTERN --------------------------------

SphereMesh::SphereMesh(float radius_, int density) : radius(radius_) {
  Generate(density);
}

void SphereMesh::Generate(int density) {
  // 1) Generate sphere mesh
  SpherifiedCube(density / 6, *this);

  // 2) Heightmap
  Vec3 origin{0., 0., 0.};
  for (auto &vertex : vertices) {
    auto &v = vertex.position;
    Vec3 normal = glm::normalize(v - origin);
    // First we extend the sphere outwards to the real radius
    v += normal * radius;
    // Next we can apply the noise
    v += normal * glm::simplex(v) / 10.f;
  }
}

int SphereMesh::addVertex(Vec3 v) {
  type::Vertex vertex;
  vertex.position = v;

  vertices.emplace_back(std::move(vertex));
  return vertices.size() - 1;
}

std::ostream &operator<<(std::ostream &o, const SphereMesh &mesh) {
  o << "OFF\n";
  o << mesh.vertices.size() << ' ' << mesh.faces.size() << " 0\n";
  for (const type::Vertex &v : mesh.vertices) {
    for (int i = 0; i < 3; i++) {
      o << v.position[i] << " ";
    }
    o << '\n';
  }
  o << '\n';
  for (const type::Face &f : mesh.faces) {
    o << "3 "; // Number of vertex per face (we're drawing triangles)
    for (int i = 0; i < 3; i++) {
      o << f[i] << " ";
    }
    o << '\n';
  }
  o.flush();
  return o;
}
