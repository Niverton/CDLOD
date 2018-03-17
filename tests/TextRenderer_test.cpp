/*! \file TextRenderer_test.cpp
 *  \brief TextRenderer unit tests.
 *  List of functions tested here:
 *      - UpdateBuffer
 */

#include "stdafx.h"

#include "TextRenderer.h"
#include "TextRenderer_test.h"

#include <algorithm>
#include <string>

static bool update_buffer_result = false;

void test_update_buffer(TextRenderer::TextVertex *buffer, size_t size) {
  update_buffer_result = true;
}

bool test() {
  bool result = true;
  TextRenderer *trp = TextRenderer::GetInstance();
  auto &tr = *trp;
  // DrawText expects a non-const l-value reference
  std::string str = "aaaa";
  tr.DrawText(str, {0, 0});
  tr.UpdateBuffer();
  result = result and update_buffer_result;

  return result;
}
