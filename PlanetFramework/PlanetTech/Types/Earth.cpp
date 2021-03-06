#include "Earth.h"
#include "Planet.h"
#include "Texture.h"

Earth::Earth() {
  m_pDiffuse = new Texture("./Textures/Earth8k.jpg");
  m_pHeight = new Texture("./Textures/EarthHeight8k.jpg");

  m_Radius = 6371.1f;
  m_MaxHeight = 8.848f;
}
