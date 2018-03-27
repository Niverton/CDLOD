#include "Procedural.h"
#include "../../Texture.h"
#include "stdafx.h"
#include <IL/il.h>
#include <IL/ilu.h>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>

ProceduralPlanet::ProceduralPlanet(Noise n) : Planet() {
  m_pDiffuse = new Texture("./Textures/moon8k.jpg");
  // m_pHeight = new Texture("./Textures/MoonHeight.jpg");
  // Compute texture here
  const int h = 2048; // same as moonHeight
  const int w = 4096;

  m_data = new float *[h];
  for (int i = 0; i < h; i++) {
    m_data[i] = new float[w];
  }

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      glm::vec2 pos = glm::vec2(i, j);
      float noise = glm::simplex(pos);
      m_data[i][j] = noise;
    }
  }

  ///*
  int wd1 = 800;
  int hd1 = 800;

  m_dataDetail1 = new float*[hd1];
  for (int i=0; i<hd1; i++){
    m_dataDetail1[i] = new float[wd1];
  }

  for (int i=0; i<hd1; i++){
    for (int j=0; j<wd1; j++){
      glm::vec2 pos = glm::vec2(i, j);
      float noise = glm::simplex(pos);
      m_dataDetail1[i][j] = noise;
    }
  }

  int wd2 = 1024;
  int hd2 = 1024;

  m_dataDetail2 = new float*[hd2];
  for (int i=0; i<h; i++){
    m_dataDetail2[i] = new float[wd2];
  }

  for (int i=0; i<hd2; i++){
    for (int j=0; j<wd2; j++){
      glm::vec2 pos = glm::vec2(i, j);
      float noise = glm::simplex(pos);
      m_dataDetail2[i][j] = noise;
    }
  }

  m_pDetail1 = new Texture(m_dataDetail1, wd1, hd1);
  m_pDetail2 = new Texture(m_dataDetail2, wd2, hd2);
  m_pHeightDetail = new Texture(m_dataDetail1, wd1, hd1);
  //*/

  m_Radius = 1737.1f;
  m_MaxHeight = 10.7f;

  m_pHeight = new Texture(m_data, w, h);
  // m_pDiffuse = m_pHeight;
}

ProceduralPlanet::~ProceduralPlanet() {
}
