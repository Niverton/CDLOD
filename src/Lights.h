#pragma once

#include "glStd.h"

struct Material {
  Material() { memset(this, 0, sizeof(this)); }

  vec4 Ambient;
  vec4 Diffuse;
  vec4 Specular;
  vec4 Emissive;
};

struct DirectionalLight {
  DirectionalLight() { memset(this, 0, sizeof(this)); }

  vec4 Ambient;
  vec4 Diffuse;
  vec3 Direction;
  float pad;
};

struct PointLight {
  PointLight() { memset(this, 0, sizeof(this)); }

  vec4 Ambient;
  vec4 Diffuse;

  vec3 Position;
  float Range;

  vec3 Att;
  float pad;
};

struct SpotLight {
  SpotLight() { memset(this, 0, sizeof(this)); }

  vec4 Ambient;
  vec4 Diffuse;

  vec3 Position;
  float Range;

  vec3 Direction;
  float Spot;

  vec3 Att;
  float Pad;
};