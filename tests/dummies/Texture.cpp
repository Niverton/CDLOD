#include "Texture.h"

Texture::Texture(std::string filename)
    : m_Name{std::move(filename)}, m_isFile{true} {
}

Texture::Texture(float *data, int width, int height)
    : m_isFile{false}, m_data{data}, m_Width{width}, m_Height{height} {
}

void Texture::Load(bool useSRGB) {
}

Texture::~Texture() {
}
