#include "Procedural.h"
#include "stdafx.h"
#include <IL/il.h>
#include <IL/ilu.h>
#include "../../Texture.h"

ProceduralPlanet::ProceduralPlanet() : Planet() {
  //m_pDiffuse = new Texture("./Textures/moon8k.jpg");
  //m_pHeight = new Texture("./Textures/MoonHeight.jpg");

  //Compute texture here
  
  ILuint img;
  ilGenImages(1, &img);
  ilBindImage(img);


  ILuint *data = nullptr;

  m_Radius = 1737.1f;
  m_MaxHeight = 10.7f;
}

ProceduralPlanet::~ProceduralPlanet() {
}
