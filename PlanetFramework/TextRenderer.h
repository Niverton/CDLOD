#pragma once

class SpriteFont;
class Shader;

class TextRenderer : public Singleton<TextRenderer> {
public:
#undef DrawText
  void DrawText(std::string &text, glm::vec2 pos);
  void SetFont(SpriteFont *pFont);
  void SetColor(glm::vec4 color) {
    m_Color = color;
  }

private:
  friend class Singleton<TextRenderer>;
  friend class Scene;

  TextRenderer();
  ~TextRenderer();

  struct TextVertex {
    glm::vec3 Position;
    glm::vec4 Color;
    glm::vec2 TexCoord;
    glm::vec2 CharacterDimension;
    unsigned int ChannelId;
  };

#ifdef TEST_textrenderer
  friend bool test();
  friend void test_update_buffer(TextRenderer::TextVertex *, size_t);
#endif

  void Init();
  void Draw();
  void UpdateBuffer();

  Shader *m_pTextShader;
  std::vector<SpriteFont *> m_pSpriteFonts;

  unsigned int m_BufferSize, m_NumCharacters;
  glm::mat4 m_Transform;
  glm::vec4 m_Color = glm::vec4(0, 0, 0, 1);
  size_t m_ActiveFontIdx;

  GLint m_uTransform;
  GLint m_uTexSize;
  GLint m_uTexture;

  GLuint m_VAO;
  GLuint m_VBO;
};
