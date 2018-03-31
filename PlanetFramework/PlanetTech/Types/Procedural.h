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
    WRAPPED_FBM
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
