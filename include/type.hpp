#pragma once

#include <glm/glm.hpp>

namespace type{
  struct Vertex{
    glm::vec4 position;
    glm::vec4 color;
  };

  using Face = glm::ivec3;
}
