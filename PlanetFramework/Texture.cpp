#include "Texture.h"
#include "stdafx.h"

#include <IL/il.h>
#include <IL/ilu.h>
//#include <IL/ilut.h>

Texture::Texture(const std::string &filename) {
  m_Name = filename;
  m_isFile = true;
}

Texture::Texture(float *data, int width, int height)
    : m_data{data}, m_Width{width}, m_Height{height}, m_isFile{false} {
}

void Texture::Load(bool useSRGB) {

  std::cout << "Loading Texture: " << m_Name << " . . . ";

  if (m_isFile == true) {
#ifdef PLATFORM_Linux
    std::string name = m_Name;
#else
    std::wstring name(m_Name.begin(), m_Name.end());
#endif

    glGenTextures(1, &m_Handle);
    glBindTexture(GL_TEXTURE_2D, m_Handle);

    ILuint imgName;
    ilGenImages(1, &imgName);
    ilBindImage(imgName);
    if (ilLoadImage(name.c_str())) {
      ilConvertImage(IL_RGB, IL_FLOAT);

      m_Width = ilGetInteger(IL_IMAGE_WIDTH);
      m_Height = ilGetInteger(IL_IMAGE_HEIGHT);
      ILubyte *pixelData = ilGetData();

      glTexImage2D(GL_TEXTURE_2D, 0, useSRGB ? GL_SRGB : GL_RGB, m_Width,
                   m_Height, 0, GL_RGB, GL_FLOAT, pixelData);

      ilBindImage(0);
      ilDeleteImage(imgName);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      std::cout << "  . . . SUCCESS!" << std::endl;
    } else {
      ILenum error = ilGetError();
      std::cout << "  . . . FAILED! DevIL error: " << std::endl
                << error << " - " << iluErrorString(error) << std::endl;
      ilBindImage(0);
      ilDeleteImage(imgName);
    }
  } else {

    glGenTextures(1, &m_Handle);
    glBindTexture(GL_TEXTURE_2D, m_Handle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, m_Width, m_Height, 0, GL_RED,
                 GL_FLOAT, m_data);
  }
}

Texture::~Texture() {
  glDeleteTextures(1, &m_Handle);
}
