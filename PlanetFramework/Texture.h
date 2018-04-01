#pragma once
#include <IL/il.h>
#include <IL/ilu.h>

#include "glad.h" // for GLuint
#include <string> // for string

#if PLATFORM_Win
#include <glm\glm.hpp>
#else
#include <glm/glm.hpp>
#endif

class Texture {
public:
  Texture(const std::string &filename);
  Texture(float *data, int width, int height);
  virtual ~Texture();

  virtual void Load(bool useSRGB);
  GLuint GetHandle() {
    return m_Handle;
  }

  glm::vec2 GetDimension() {
    return glm::vec2(m_Width, m_Height);
  }

private:
  std::string m_Name;
  bool m_isFile = true;
  float *m_data = nullptr;

protected:
  GLuint m_Handle{};
  int m_Width{};
  int m_Height{};
};
