#include "Procedural.h"
#include "../../Texture.h"
#include "stdafx.h"
#include <IL/il.h>
#include <IL/ilu.h>
#include <vector>
#include "Simplex.h"

#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>

ProceduralPlanet::ProceduralPlanet(Noise n, Properties* properties) {
  
  unsigned int width = properties->width;
  unsigned int height = properties->height;
  m_Radius = properties->radius;
  m_MaxHeight = properties->maxHeight;

  m_data = new float[height * width];
  for (int i = 0; i < height * width; i++) {
    switch (n){
      case Noise::SIMPLEX: default:
        m_data[i] = glm::simplex(glm::vec3(i % width, i / width, 1.));
        break;
      case Noise::PERLIN:
        m_data[i] = glm::perlin(glm::vec3(i % width, i / width, 1.));
        break;
      case Noise::RIDGED_NOISE:
        m_data[i] = Simplex::ridgedNoise(glm::vec3(i % width, i / width, 1.));
        break;
      case Noise::FLOW_NOISE:
      {
        auto prop = static_cast<FlowNoiseProperties*>(properties);
        m_data[i] = Simplex::flowNoise(glm::vec3(i % width, i / width, 1.), prop->angle);
        break;
      }
      case Noise::FBM:
      {
        auto prop = static_cast<FbmProperties*>(properties);
        m_data[i] = Simplex::fBm(glm::vec3(i % width, i / width, 1.),
                    prop->octave, prop->lacunarity, prop->gain);
        break;
      }
      case Noise::WRAPPED_FBM:
      {
        auto prop = static_cast<FbmProperties*>(properties);
        m_data[i] = Simplex::fBm(Simplex::fBm(glm::vec3(i % width, i / width, 1.),
                    prop->octave, prop->lacunarity, prop->gain));
        break;
      }
    }
  }

  m_pHeight = new Texture(m_data, width, height);
  //m_pDiffuse = new Texture(m_data, width, height);
  m_pDiffuse = new Texture("./Textures/moon8k.jpg");
}

ProceduralPlanet::~ProceduralPlanet() {
  delete[] m_data;
}
