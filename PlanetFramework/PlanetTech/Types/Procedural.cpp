#include "Procedural.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>

ProceduralPlanet::ProceduralPlanet(Noise n) {
  m_pDiffuse = new Texture("./Textures/moon8k.jpg");
  // m_pHeight = new Texture("./Textures/MoonHeight.jpg");
  // Compute texture here
  const int h = 2048; // same as moonHeight
  const int w = 2048;

  auto *data = new float[h * w];
  for (int i = 0; i < h * w; i++) {
    data[i] = glm::simplex(glm::vec3(i % w, i / w, 1.));
  }

  // Taken from Moon
  m_Radius = 1737.1f;
  m_MaxHeight = 10.7f;

  m_pHeight = new Texture(data, w, h);
}

ProceduralPlanet::~ProceduralPlanet() {
}
