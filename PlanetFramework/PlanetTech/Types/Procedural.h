#pragma once
#include "Planet.h"
#include <string>

class ProceduralPlanet : public Planet {
public:
  enum class Noise : int {
    SIMPLEX = 0,
    PERLIN = 1,
    RIDGED_NOISE = 2,
    FLOW_NOISE = 3,
    FBM = 4,
    WARPED_FBM = 5,
    DFBM_WARPED_FBM = 6,
    RIDGED_MULTI_FRACTAL = 7,
  };

  struct Properties {
    Noise noise = Noise::SIMPLEX;        //default
    unsigned int width = 1024;
    unsigned int height = 1024;
    unsigned int octave = 4;
    float radius = 1737.1f;       //Same as moon
    float maxHeight = 10.7f;      //Same as moon
    float lacunarity = 2.0f;
    float gain = 0.5f;
    float angle = 0.5f;
    float ridgeOffset = 0.1f;
  };

  ProceduralPlanet(Properties* prop);
  ~ProceduralPlanet();

private:
  float* m_data;
};

