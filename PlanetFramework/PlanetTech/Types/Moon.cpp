#include "Moon.h"
#include "stdafx.h"

#include "../../Texture.h"

Moon::Moon() : Planet() {
  m_pDiffuse = new Texture("./Textures/moon8k.jpg");
  m_pHeight = new Texture("./Textures/MoonHeight.jpg");

  m_pDetail1 = new Texture("./Textures/MoonDetail1.jpg");
  m_pDetail2 = new Texture("./Textures/MoonDetail2.jpg");
  m_pHeightDetail = new Texture("./Textures/MoonHeightDetail1.jpg");

  m_Radius = 1737.1f;
  m_MaxHeight = 10.7f;
}
Moon::~Moon() {
}
