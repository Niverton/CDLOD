#include "Procedural.h"
#include "stdafx.h"

#include "../../Texture.h"

ProceduralPlanet::ProceduralPlanet() : Planet() {
  //m_pDiffuse = new Texture("./Textures/moon8k.jpg");
  //m_pHeight = new Texture("./Textures/MoonHeight.jpg");

  //Compute texture here
//  m_pHeight = 

  m_Radius = 1737.1f;
  m_MaxHeight = 10.7f;
}

ProceduralPlanet::~ProceduralPlanet() {
}
