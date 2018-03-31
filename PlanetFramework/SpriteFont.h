#pragma once

#include "utils.h" // for UCHAR, USHORT
#include <string>  // for string
#include <vector>  // for vector

#if PLATFORM_Win
#include <SDL.h>
#include <glm\glm.hpp>
#else
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#endif
class Texture; // lines 31-31

struct TextCache {
public:
  TextCache(const std::string &text, glm::vec2 pos, glm::vec4 col)
      : Text(text), Position(pos), Color(col) {
  }

  const std::string Text;
  glm::vec2 Position;
  glm::vec4 Color;

private:
  TextCache &operator=(const TextCache &tmp);
};

struct FontMetric {
  // BMFONT
  bool IsValid = false;
  wchar_t Character = 0;
  unsigned short Width = 0;
  unsigned short Height = 0;
  short OffsetX = 0;
  short OffsetY = 0;
  short AdvanceX = 0;
  unsigned char Page = 0;
  unsigned char Channel = 0;
  glm::vec2 TexCoord;
};

class Texture;
class TextRenderer;

class SpriteFont {
public:
  SpriteFont() = default;
  virtual ~SpriteFont() {
    SafeDelete(m_pTexture);
  };
  SpriteFont(const SpriteFont &t) = delete;
  SpriteFont &operator=(const SpriteFont &t) = delete;

  static bool IsCharValid(const wchar_t &character);

  void Load(std::string filename);

  static const int MAX_CHAR_ID = 255;
  static const int MIN_CHAR_ID = 0;
  static const int CHAR_COUNT = MAX_CHAR_ID - MIN_CHAR_ID + 1;

private:
  friend class TextRenderer;
#ifdef test_textrenderer_update_buffer
  friend void test_update_buffer(void *, size_t);
#endif

  FontMetric &GetMetric(const wchar_t &character) {
    return m_CharTable[character - MIN_CHAR_ID];
  };

  FontMetric m_CharTable[CHAR_COUNT];
  std::vector<TextCache> m_TextCache;

  short m_FontSize = 0;
  std::string m_FontName;
  int m_CharacterCount = 0;
  int m_CharacterSpacing = 1;
  int m_TextureWidth = 0;
  int m_TextureHeight = 0;
  int m_BufferStart = 0;
  int m_BufferSize = 0;
  Texture *m_pTexture = nullptr;
  bool m_IsAddedToRenderer = false;
};
