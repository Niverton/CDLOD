/*! \file Shader.cpp
 *  \brief Dummy link target
 */

#include <string>

#include "Shader.h"

Shader::Shader(std::string filename, bool build) {
}

void Shader::Build() {
}

GLuint Shader::CompileShader(const std::string &shaderSourceStr, GLenum type) {
  return 0;
}

Shader::~Shader() {
}
