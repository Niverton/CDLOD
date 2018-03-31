#pragma once
#include "../Planet.h"

class ProceduralPlanet : public Planet {
public:
  enum class Noise {
    SIMPLEX, 
    PERLIN,
    RIDGED_NOISE,
    FLOW_NOISE,
    FBM,
    FBM_VARIATION,
    WARPED_FBM,
    DFBM_WARPED_FBM,
    RIDGED_MULTI-FRACTAL_VARIATION,
    WARPED_RIDGED_MULTI-FRACTAL,
    RIDGED_MULTI-FRACTAL_VARIATION2,
  };

  struct Properties {
  public:
    unsigned int width = 1024;
    unsigned int height = 1024;
    float radius = 1737.1f;       //Same as moon
    float maxHeight = 10.7f;      //Same as moon
  };

  ProceduralPlanet(Noise n, Properties* properties);
  ~ProceduralPlanet();

private:
  float* m_data;
};


struct FlowNoiseProperties : ProceduralPlanet::Properties {
  float angle;
};

struct FbmProperties : ProceduralPlanet::Properties {
  unsigned short octave = 4;
  float lacunarity = 2.0f;
  float gain = 0.5f;
};

struct FbmVariationProperties : ProceduralPlanet::Properties {
  unsigned short octave = 10;
  float lacunarity = 5.0f;
  float gain = 0.75f;
};


struct DfbmProperties : ProceduralPlanet::Properties {
  unsigned short octave = 4;
  float lacunarity = 2.0f;
  float gain = 0.5f;
};

struct RidgedMultiFractalVariationProperties : ProceduralPlanet::Properties {
  float ridgeOffset = 0.1f;
  unsigned short octave = 5;
  float lacunarity = 1.5f;
  float gain = 1.5f;
};

struct WarpedRidgedMultiFractalProperties : ProceduralPlanet::Properties {
  float ridgeOffset = 1.0f;
  unsigned short octave = 4;
  float lacunarity = 2.0f;
  float gain = 0.5f;
};

struct WarpedRidgedMultiFractal2Properties : ProceduralPlanet::Properties {
  float ridgeOffset = -1.0f;
  unsigned short octave = 4;
  float lacunarity = 3.0f;
  float gain = -0.65f;
};