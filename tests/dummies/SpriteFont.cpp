#include "stdafx.h"

#include "SpriteFont.h"

#include "BinaryReader.h"
#include "Texture.h"

SpriteFont::SpriteFont() {
}

SpriteFont::~SpriteFont() {
}

bool SpriteFont::IsCharValid(const wchar_t &character) {
  if (character >= MIN_CHAR_ID && character <= MAX_CHAR_ID) {
    return true;
  }
  return false;
}

void SpriteFont::Load(std::string filename) {
  m_FontName = "DummyFont";
  m_CharacterCount = 1;
  auto &m = m_CharTable[0];
  m.IsValid = true;
  m.Character = 0;
  m.Width = 10;
  m.Height = 10;
  m.OffsetX = 0;
  m.OffsetY = 0;
  m.AdvanceX = 0;
  m.Page = 0;
  m.Channel = 0;
  m.TexCoord = {0, 0};
}
