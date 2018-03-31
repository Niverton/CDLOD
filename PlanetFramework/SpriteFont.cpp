#include "SpriteFont.h"
#include "BinaryReader.h" // for BinaryReader
#include "Texture.h"      // for Texture
#include "utils.h"        // for SafeDelete
#include <iostream>       // for operator<<, basic_ostream, endl, cout, ost...

bool SpriteFont::IsCharValid(const wchar_t &character) {
  return character >= MIN_CHAR_ID && character <= MAX_CHAR_ID;
}

void SpriteFont::Load(const std::string &filename) {
  auto pBinReader = new BinaryReader(); // Prevent memory leaks
  pBinReader->Open(filename);

  if (!pBinReader->Exists()) {
    delete pBinReader;
    std::cout << "[ERROR] "
              << "SpriteFont::Load > Failed to read the assetFile!\nPath: "
              << filename << std::endl;

    return;
  }
  bool valid = false;
  if (pBinReader->Read<char>() == 'B') {
    if (pBinReader->Read<char>() == 'M') {
      if (pBinReader->Read<char>() == 'F') {
        valid = true;
      }
    }
  }
  if (!valid) {
    std::cerr << "[ERROR] Font file header invalid!\n";
    return;
  }
  if (pBinReader->Read<char>() < 3) {
    std::cerr << "[ERROR] Font version invalid!\n";
    return;
  }

  //**********
  // BLOCK 0 *
  //**********
  pBinReader->Read<char>();
  auto Block0Size = pBinReader->Read<int>();
  int pos = pBinReader->GetBufferPosition();
  m_FontSize = pBinReader->Read<short>();
  pBinReader->SetBufferPosition(pos + 14);
  std::string fn;
  auto cur = pBinReader->Read<char>();
  while (cur != '\0') {
    fn += cur;
    cur = pBinReader->Read<char>();
  }
  m_FontName = fn;
  pBinReader->SetBufferPosition(pos + Block0Size);
  //**********
  // BLOCK 1 *
  //**********
  pBinReader->Read<char>();
  auto Block1Size = pBinReader->Read<int>();
  pos = pBinReader->GetBufferPosition();
  pBinReader->SetBufferPosition(pos + 4);
  m_TextureWidth = pBinReader->Read<unsigned short>();
  m_TextureHeight = pBinReader->Read<unsigned short>();
  auto pagecount = pBinReader->Read<unsigned short>();
  if (pagecount > 1) {
    std::cerr << "[ERROR] SpriteFont::Load > SpriteFont(.fnt): Only one "
                 "texture per font allowed\n";
  }
  pBinReader->SetBufferPosition(pos + Block1Size);
  //**********
  // BLOCK 2 *
  //**********
  pBinReader->Read<char>();
  auto Block2Size = pBinReader->Read<int>();
  pos = pBinReader->GetBufferPosition();
  std::string pn;
  cur = pBinReader->Read<char>();
  while (cur != '\0') {
    pn += cur;
    cur = pBinReader->Read<char>();
  }
  if (pn.empty()) {
    std::cerr << "[ERROR] SpriteFont::Load > SpriteFont(.fnt): Invalid Font "
                 "Sprite [Empty]\n";
  }
  auto filepath = filename.substr(0, filename.rfind('/') + 1);
  m_pTexture = new Texture(filepath + pn);
  m_pTexture->Load(false);
  pBinReader->SetBufferPosition(pos + Block2Size);
  //**********
  // BLOCK 3 *
  //**********
  pBinReader->Read<char>();
  auto Block3Size = pBinReader->Read<int>();
  // pos = pBinReader->GetBufferPosition();
  auto numChars = Block3Size / 20;
  m_CharacterCount = numChars;
  for (int i = 0; i < numChars; i++) {
    auto posChar = pBinReader->GetBufferPosition();
    auto charId = static_cast<wchar_t>(pBinReader->Read<unsigned int>());
    if (!(IsCharValid(charId))) {
      std::cerr << "[WARNING] SpriteFont::Load > SpriteFont(.fnt): Invalid "
                   "Character\n";
      pBinReader->SetBufferPosition(posChar + 20);
    } else {
      auto metric = &GetMetric(charId);
      metric->IsValid = true;
      metric->Character = charId;
      auto xPos = pBinReader->Read<unsigned short>();
      auto yPos = pBinReader->Read<unsigned short>();
      metric->Width = pBinReader->Read<unsigned short>();
      metric->Height = pBinReader->Read<unsigned short>();
      metric->OffsetX = pBinReader->Read<short>();
      metric->OffsetY = pBinReader->Read<short>();
      metric->AdvanceX = pBinReader->Read<short>();
      metric->Page = pBinReader->Read<unsigned char>();
      auto chan = pBinReader->Read<unsigned char>();
      switch (chan) {
      case 1:
        metric->Channel = 2;
        break;
      case 2:
        metric->Channel = 1;
        break;
      case 4:
        metric->Channel = 0;
        break;
      case 8:
        metric->Channel = 3;
        break;
      default:
        metric->Channel = 4;
        break;
      }
      metric->TexCoord = glm::vec2(float(xPos) / float(m_TextureWidth),
                                   float(yPos) / float(m_TextureHeight));
      pBinReader->SetBufferPosition(posChar + 20);
    }
  }
  delete pBinReader;
}
