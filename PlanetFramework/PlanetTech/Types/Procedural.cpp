#include "Procedural.h"
#include "Simplex.h"
#include "Texture.h"
#include <cmath>
#include <functional>
#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>

/*
static double gaussian(double x, double y, double sigma) {
  double a = (1. / (2 * M_PI * sigma * sigma));
  double b = -((x * x + y * y) / (2 * sigma * sigma));
  return a * std::exp(b);
}
*/

ProceduralPlanet::ProceduralPlanet(Properties *prop) {
  unsigned int width = prop->width;
  unsigned int height = prop->height;
  m_Radius = prop->radius;
  m_MaxHeight = prop->maxHeight;
  Noise n = prop->noise;

  std::function<double(glm::vec3)> noise_maker;
  /* Added NOLINT to prevent clang-tidy from flagging suspicious but
   * legit static_casts
   */
  switch (n) {
  case Noise::SIMPLEX:
  default:
    noise_maker = [](const glm::vec3 &p) { return glm::simplex(p); };
    break;
  case Noise::PERLIN:
    noise_maker = [](const glm::vec3 &p) { return glm::perlin(p); };
    break;
  case Noise::RIDGED_NOISE:
    noise_maker = [](const glm::vec3 &p) { return Simplex::ridgedNoise(p); };
    break;
  case Noise::FLOW_NOISE: {
    noise_maker = [&](const glm::vec3 &p) {
      return Simplex::flowNoise(p, prop->angle);
    };
  } break;
  case Noise::FBM: {
    noise_maker = [&](const glm::vec3 &p) {
      return Simplex::fBm(p, prop->octave, prop->lacunarity, prop->gain);
    };
  } break;
  case Noise::WARPED_FBM: {
    noise_maker = [&](const glm::vec3 &p) {
      return Simplex::fBm(
          Simplex::fBm(p, prop->octave, prop->lacunarity, prop->gain),
          prop->octave, prop->lacunarity, prop->gain);
    };
  } break;
  case Noise::DFBM_WARPED_FBM: {
    noise_maker = [&](const glm::vec3 &p) {
      return Simplex::fBm(
          Simplex::dfBm(p, prop->octave, prop->lacunarity, prop->gain),
          prop->octave, prop->lacunarity, prop->gain);
    };
  } break;

  case Noise::RIDGED_MULTI_FRACTAL: {
    noise_maker = [&](const glm::vec3 &p) {
      return Simplex::ridgedMF(p, prop->ridgeOffset, prop->octave,
                               prop->lacunarity, prop->gain);
    };
  } break;
  }

  m_data = new float[height * width];
  for (unsigned int i = 0; i < height * width; i++) {
    double x = std::fmod(double(i), double(width));
    double y = std::floor(double(i) / double(width));
    double u = x / double(width);
    double v = y / double(width);
    double theta = 2 * M_PI * u;
    double phi = M_PI * v;
    glm::vec3 p{std::cos(theta) * std::cos(phi) * m_Radius,
                std::sin(theta) * std::cos(phi) * m_Radius,
                std::sin(phi) * m_Radius};
    // Low pass filter
    m_data[i] = ((noise_maker(p) + 1.) / 2.);// * gaussian(u, v, 1.5);
  }

  m_pHeight = new Texture(m_data, width, height);
  // m_pDiffuse = new Texture(m_data, width, height);
  m_pDiffuse = new Texture("./Textures/moon8k.jpg");
}

ProceduralPlanet::~ProceduralPlanet() {
  delete[] m_data;
}
