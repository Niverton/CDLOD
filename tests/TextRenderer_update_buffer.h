#pragma once

#include "TextRenderer.h"

#include "disable_gl.h"

#undef glBufferData
#define glBufferData(type, size, buffer, mode) test_update_buffer(buffer, size)

void test_update_buffer(TextRenderer::TextVertex *buffer, size_t size);
