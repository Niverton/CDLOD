#include "TextRenderer.h"
#include "Settings.h"   // for Settings::WindowSettings
#include "Shader.h"     // for Shader
#include "SpriteFont.h" // for SpriteFont, FontMetric, TextCache
#include "Texture.h"    // for Texture
#include "utils.h"      // for WINDOW, SafeDelete
#include <algorithm>    // for find
#include <iostream>     // for operator<<, endl, basic_ostream
#include <iterator>     // for each loop (begin and end)

#if PLATFORM_Win
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#else
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif

TextRenderer::TextRenderer() {
  m_pTextShader = new Shader("./Shaders/text.glsl");
}

TextRenderer::~TextRenderer() {
  SafeDelete(m_pTextShader);
  glDeleteVertexArrays(1, &m_VAO);
  glDeleteBuffers(1, &m_VBO);
}

void TextRenderer::Init() {
  m_pTextShader->Build();
  glUseProgram(m_pTextShader->GetProgram());
  m_uTransform = glGetUniformLocation(m_pTextShader->GetProgram(), "transform");
  m_uTexSize = glGetUniformLocation(m_pTextShader->GetProgram(), "texSize");

  m_uTexture = glGetUniformLocation(m_pTextShader->GetProgram(), "fontTex");
  glUniform1i(m_uTexture, 0);

  // Generate buffers and arrays
  glGenVertexArrays(1, &m_VAO);
  glGenBuffers(1, &m_VBO);

  // bind
  glBindVertexArray(m_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

  // set data and attributes
  glBufferData(GL_ARRAY_BUFFER, m_BufferSize, nullptr, GL_DYNAMIC_DRAW);

  // input layout

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);
  glEnableVertexAttribArray(4);

  glVertexAttribPointer(
      0, static_cast<GLint>(3), GL_FLOAT, GL_FALSE,
      static_cast<GLsizei>(sizeof(TextVertex)),
      reinterpret_cast<GLvoid *>(offsetof(TextVertex, Position)));
  glVertexAttribPointer(
      1, static_cast<GLint>(4), GL_FLOAT, GL_FALSE,
      static_cast<GLsizei>(sizeof(TextVertex)),
      reinterpret_cast<GLvoid *>(offsetof(TextVertex, Color)));
  glVertexAttribPointer(
      2, static_cast<GLint>(2), GL_FLOAT, GL_FALSE,
      static_cast<GLsizei>(sizeof(TextVertex)),
      reinterpret_cast<GLvoid *>(offsetof(TextVertex, TexCoord)));
  glVertexAttribPointer(
      3, static_cast<GLint>(2), GL_FLOAT, GL_FALSE,
      static_cast<GLsizei>(sizeof(TextVertex)),
      reinterpret_cast<GLvoid *>(offsetof(TextVertex, CharacterDimension)));
  glVertexAttribIPointer(
      4, static_cast<GLint>(1), GL_UNSIGNED_INT,
      static_cast<GLsizei>(sizeof(TextVertex)),
      reinterpret_cast<GLvoid *>(offsetof(TextVertex, ChannelId)));

  // unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  float scaleX = (WINDOW.Width > 0) ? 2.f / WINDOW.Width : 0;
  float scaleY = (WINDOW.Height > 0) ? 2.f / WINDOW.Height : 0;

  float aaa[16]{scaleX, 0, 0, 0, 0, -scaleY, 0, 0, 0, 0, 1, 0, -1, 1, 0, 1};
  m_Transform = glm::make_mat4(static_cast<float *>(aaa));
}

void TextRenderer::SetFont(SpriteFont *pFont) {
  auto pos = std::find(m_pSpriteFonts.begin(), m_pSpriteFonts.end(), pFont);
  if (pos == m_pSpriteFonts.end()) {
    m_ActiveFontIdx = m_pSpriteFonts.size();
    m_pSpriteFonts.push_back(pFont);
  } else {
    m_ActiveFontIdx = pos - m_pSpriteFonts.begin();
  }
}

void TextRenderer::DrawText(const std::string &text, glm::vec2 pos) {
  if (!m_pSpriteFonts.empty()) {
    m_NumCharacters += text.size();
    m_pSpriteFonts[m_ActiveFontIdx]->m_TextCache.emplace_back(text, pos,
                                                              m_Color);
    if (!m_pSpriteFonts[m_ActiveFontIdx]->m_IsAddedToRenderer) {
      m_pSpriteFonts[m_ActiveFontIdx]->m_IsAddedToRenderer = true;
    }
  } else {
    std::cerr << "[WARNING] TextRenderer>DrawText: No active font found!\n";
  }
}

void TextRenderer::Draw() {
  if (m_pSpriteFonts.empty()) {
    return;
  }

  // Bind Object vertex array
  glBindVertexArray(m_VAO);

  UpdateBuffer();

  // Enable this objects shader
  glUseProgram(m_pTextShader->GetProgram());
  glActiveTexture(GL_TEXTURE0);
  glUniformMatrix4fv(m_uTransform, 1, GL_FALSE, glm::value_ptr(m_Transform));

  // Bind Object vertex array
  glBindVertexArray(m_VAO);
  for (auto pFont : m_pSpriteFonts) {
    if (pFont->m_IsAddedToRenderer) {
      glBindTexture(GL_TEXTURE_2D, pFont->m_pTexture->GetHandle());

      auto texSize = pFont->m_pTexture->GetDimension();
      glUniform2f(m_uTexSize, texSize.x, texSize.y);

      // Draw the object
      glDrawArrays(GL_POINTS, pFont->m_BufferStart, pFont->m_BufferSize);

      pFont->m_IsAddedToRenderer = false;
    }
  }
  // unbind vertex array
  glBindVertexArray(0);
}

void TextRenderer::UpdateBuffer() {
  std::vector<TextVertex> tVerts;
  for (auto pFont : m_pSpriteFonts) {
    if (pFont->m_IsAddedToRenderer) {
      pFont->m_BufferStart =
          tVerts.size() * (sizeof(TextVertex) / sizeof(float));
      pFont->m_BufferSize = 0;
      for (auto cache : pFont->m_TextCache) {
        int totalAdvanceX = 0;
        for (auto charId : cache.Text) {
          if (SpriteFont::IsCharValid(charId) &&
              pFont->GetMetric(charId).IsValid) {
            auto metric = pFont->GetMetric(charId);

            if (charId == ' ') {
              totalAdvanceX += metric.AdvanceX;
              continue;
            }

            TextVertex vText;
            vText.Position.x =
                cache.Position.x + totalAdvanceX + metric.OffsetX;
            vText.Position.y = cache.Position.y + metric.OffsetY;
            vText.Position.z = 0;
            vText.Color = cache.Color;
            vText.TexCoord = metric.TexCoord;
            vText.CharacterDimension = glm::vec2(metric.Width, metric.Height);
            vText.ChannelId = metric.Channel;

            tVerts.push_back(vText);

            totalAdvanceX += metric.AdvanceX;
          } else {
            std::cerr << "[WARNING] TextRenderer::CreateTextVertices>char not "
                         "suppported for current font\n";
          }
        }
      }
      pFont->m_BufferSize = tVerts.size() - pFont->m_BufferStart + 1;
      pFont->m_TextCache.clear();
    }
  }

  // Bind Object vertex array
  glBindVertexArray(m_VAO);

  unsigned int buffersize = tVerts.size() * sizeof(TextVertex);

  // Send the vertex buffer again
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, buffersize, tVerts.data(), GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Done Modifying
  glBindVertexArray(0);

  m_NumCharacters = 0;
}
