/*! \file TextRenderer_test.cpp
 *  \brief TextRenderer unit tests.
 *  List of functions tested here:
 *      - UpdateBuffer
 */

#include "TextRenderer_update_buffer.h"
#include "TextRenderer.h"

#include <algorithm>
#include <iostream>
#include <string>

static bool update_buffer_result = false;

static SpriteFont font;
static std::string data;

void test_update_buffer(void *buffer, size_t size) {
  using glm::vec3;
  vec3 ep = {0, 0, 0};
  const auto *ptr = static_cast<TextRenderer::TextVertex *>(buffer);
  for (size_t i = 0; i < size; i++) {
    FontMetric &m = font.GetMetric(data[i]);
    const vec3 &p = ptr[i].Position;
    if (p != ep + vec3{m.OffsetX, m.OffsetY, 0}) {
      return;
    }
    ep += vec3{m.AdvanceX, 0, 0};
  }

  update_buffer_result = true;
}

bool test() {
  auto &tr = *TextRenderer::GetInstance();
  // DrawText expects a non-const l-value reference
  font.Load("PlanetFramework/Fonts/Consolas_32.fnt");
  tr.SetFont(&font);
  data = "abcd";
  tr.DrawText(data, {0, 0});
  tr.UpdateBuffer();

  return update_buffer_result;
}
