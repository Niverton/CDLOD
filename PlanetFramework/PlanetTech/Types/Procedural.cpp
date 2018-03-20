#include <array>
#include "Procedural.h"
#include "stdafx.h"
#include <IL/il.h>
#include <IL/ilu.h>
#include "../../Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>

ProceduralPlanet::ProceduralPlanet() : Planet() {
  //m_pDiffuse = new Texture("./Textures/moon8k.jpg");
  //m_pHeight = new Texture("./Textures/MoonHeight.jpg");

  //Compute texture here
  const int h = 2048;    //same as moonHeight
  const int w = 4096;

  auto data = std::array<ILubyte, h*w>();

  for (int i=0; i<h; i++){
    for (int j=0; j<w; j++){
      //data[i+j] = static_cast<ILubyte>(glm::simplex(i+j));
    }
  }

  m_Radius = 1737.1f;
  m_MaxHeight = 10.7f;

  //m_pHeight = new Texture(data.data());
  m_pDiffuse = m_pHeight;
}

ProceduralPlanet::~ProceduralPlanet() {
}
