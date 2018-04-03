/*!
  \brief Class Shader use for load, compile and link OpenGL shaders.
    The program cover three diffents types of shader: vertex, fragment and
    geometry shaders.
    All of these must be written in the same file and include between the good
    tags.
    - The vertex shader is included between <VERTEX> and </VERTEX> tags
    - The fragment shader is included between <FRAGMENT> and </FRAGMENT> tags
    - The geomertry shader is included between <GEOMETRY> and </GEOMETRY> tags

    The shader file must contain at least a vertex shader and a fragment
    shader.

    In the case where user create own shader file, the standard color
  destination must be named outColor like that: out vec4 outColor
*/
#pragma once

#include "glad.h" // for GLuint, GLenum
#include <string>                         // for string
class Shader {
public:
  /*!
    \param[in] filename   The path of the file in the drive
    \param[in] build      Boolean, if true, shader is loaded, compiled and
                          linked during the construction of the shader.
                          (the methode Build is used).
                          Otherwise nothing happens
  */
  Shader(std::string filename, bool build = false);
  ~Shader();

  /*!
    \brief  Load, parse, compile and link the shader file.
            An OpenGL shader program is created.
            Some compilation and lincking status has printed in standard output.
  */
  void Build();
  GLuint GetProgram() const {
    return m_ShaderProgram;
  }

  std::string GetSourceLocation() const {
    return m_FileName;
  }

private:
  GLuint CompileShader(const std::string &shaderSourceStr, GLenum type);

  GLuint m_VertexShader{};
  GLuint m_GeometryShader{};
  GLuint m_FragmentShader{};
  GLuint m_ShaderProgram{};
  bool m_UseGS = false;

  std::string m_FileName;
};
