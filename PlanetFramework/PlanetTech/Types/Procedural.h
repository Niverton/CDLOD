#pragma once
#include "../Planet.h"

class ProceduralPlanet : public Planet {
public:
  enum class Noise{
    SIMPLEX, PERLIN
  };
  ProceduralPlanet(Noise n);
  ~ProceduralPlanet();
private:
  float** m_data;
  float** m_dataDetail1;
  float** m_dataDetail2;
};
