#include "Procedural.h"
#include "Texture.h"
#include "Simplex.h"
#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>

ProceduralPlanet::ProceduralPlanet(Properties* properties) {
  
  unsigned int width = properties->width;
  unsigned int height = properties->height;
  m_Radius = properties->radius;
  m_MaxHeight = properties->maxHeight;
  Noise n = properties->noise;

  m_data = new float[height * width];
  for (unsigned int i = 0; i < height * width; i++) {
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
      case Noise::FBM_VARIATION:
      {
        auto prop = static_cast<FbmProperties*>(properties);
        m_data[i] = Simplex::fBm(Simplex::fBm(glm::vec3(i % width, i / width, 1.),
                    prop->octave, prop->lacunarity, prop->gain),prop->octave, prop->lacunarity, prop->gain);
        break;
      }
      case Noise::WARPED_FBM:
      {
        auto prop = static_cast<FbmProperties*>(properties);
        m_data[i] = Simplex::fBm(Simplex::fBm(glm::vec3(i % width, i / width, 1.),
                    prop->octave, prop->lacunarity, prop->gain),prop->octave, prop->lacunarity, prop->gain);
        break;
      }
      case Noise::DFBM_WARPED_FBM:
      {
        auto prop = static_cast<FbmProperties*>(properties);
        m_data[i] = Simplex::fBm(Simplex::dfBm(glm::vec3(i % width, i / width, 1.),
                    prop->octave, prop->lacunarity, prop->gain),prop->octave, prop->lacunarity, prop->gain);
        break;
      }  
      case Noise::RIDGED_MULTI_FRACTAL_VARIATION:
      {
        auto prop = static_cast<RidgedMultiFractalVariationProperties*>(properties);
        m_data[i] = Simplex::ridgedMF(glm::vec3(i % width, i / width, 1.),
                    prop->ridgeOffset, prop->octave, prop->lacunarity, prop->gain);
        break;
      }   
      case Noise::WARPED_RIDGED_MULTI_FRACTAL:
      {
        auto prop = static_cast<WarpedRidgedMultiFractalProperties*>(properties);
        m_data[i] = Simplex::ridgedMF(Simplex::ridgedMF(glm::vec3(i % width, i / width, 1.),
                    prop->ridgeOffset, prop->octave, prop->lacunarity, prop->gain),prop->ridgeOffset, prop->octave, prop->lacunarity, prop->gain);
        break;
      }
      case Noise::RIDGED_MULTI_FRACTAL_VARIATION2:
      {
        auto prop = static_cast<RidgedMultiFractalVariationProperties*>(properties);
        m_data[i] = Simplex::ridgedMF(glm::vec3(i % width, i / width, 1.),
                    prop->ridgeOffset, prop->octave, prop->lacunarity, prop->gain);
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
