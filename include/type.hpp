#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace type{
  using Vec2 = glm::vec2;           //glm::mediump_dvec2;
  using Vec3 = glm::vec3;           //glm::mediump_dvec3;
  using Vec4 = glm::vec4;           //glm::mediump_dvec4;

  using Vec2i = glm::ivec2;
  using Vec3i = glm::ivec3;
  using Vec4i = glm::ivec4;

  struct Vertex{
    Vec4 position;
  };

  using Face = Vec3i;
}
