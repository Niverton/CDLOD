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

  m_data = new float*[h];
  for (int i=0; i<h; i++){
    m_data[i] = new float[w];
  }

  for (int i=0; i<h; i++){
    for (int j=0; j<w; j++){
      glm::vec2 pos = glm::vec2(i, j);
      float noise = glm::simplex(pos);
      m_data[i][j] = noise;
    }
  }

  m_Radius = 1737.1f;
  m_MaxHeight = 10.7f;

  m_pHeight = new Texture(m_data);
  //m_pDiffuse = m_pHeight;
  
}

ProceduralPlanet::~ProceduralPlanet() {
}
