#include <vector>
#include "Procedural.h"
#include "stdafx.h"
#include <IL/il.h>
#include <IL/ilu.h>
#include "../../Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>

ProceduralPlanet::ProceduralPlanet(Noise n) : Planet() {
  m_pDiffuse = new Texture("./Textures/moon8k.jpg");
  //m_pHeight = new Texture("./Textures/MoonHeight.jpg");
  //Compute texture here
  const int h = 2048;    //same as moonHeight
  const int w = 4096;

  std::vector<ILubyte> data;

  
  for (int i=0; i<h; i++){
    for (int j=0; j<w; j++){
      if (n == Noise::SIMPLEX){
        data.emplace_back(static_cast<ILubyte>(glm::simplex(glm::vec2(i, j))));
      }
      if (n == Noise::PERLIN){
        //data[i+j] = static_cast<ILubyte>(glm::perlin(glm::vec2(i, j)));
      }
    }
  }

  m_Radius = 1737.1f;
  m_MaxHeight = 10.7f;

  m_pHeight = new Texture(data.data());
  //m_pDiffuse = m_pHeight;
  
}

ProceduralPlanet::~ProceduralPlanet() {
}
