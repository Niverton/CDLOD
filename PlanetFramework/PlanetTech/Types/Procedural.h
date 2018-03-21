#pragma once
#include "../Planet.h"

class ProceduralPlanet : public Planet {
public:
  enum class Noise{
    SIMPLEX, PERLIN
  };
  ProceduralPlanet(Noise n);
  ~ProceduralPlanet();
};
