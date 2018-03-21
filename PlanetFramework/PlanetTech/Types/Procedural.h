#pragma once
#include "../Planet.h"

template <typename Noise>
class ProceduralPlanet : public Planet {
public:
  ProceduralPlanet(Noise func);
  ~ProceduralPlanet();
};
