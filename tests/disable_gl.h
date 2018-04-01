/*! \file disable_gl.h
 *  \brief Disable all GL calls for testing.
 *  Expand it by trying to build your tests and adding the missing calls
 *  to suppress.
 */

/*  Vim:
 *  copy paste linker error, extracts the function names (visual block)
 *  :sort u
 *  to remove duplicate lines
 */

#pragma once

#undef glActiveTexture
#undef glAttachShader
#undef glBindBuffer
#undef glBindFragDataLocation
#undef glBindTexture
#undef glBindVertexArray
#undef glBufferData
#undef glCompileShader
#undef glCreateProgram
#undef glCreateShader
#undef glDeleteBuffers
#undef glDeleteProgram
#undef glDeleteShader
#undef glDeleteTextures
#undef glDeleteVertexArrays
#undef glDrawArrays
#undef glEnableVertexAttribArray
#undef glGenBuffers
#undef glGenTextures
#undef glGenVertexArrays
#undef glGetProgramInfoLog
#undef glGetProgramiv
#undef glGetShaderInfoLog
#undef glGetShaderiv
#undef glGetUniformLocation
#undef glLinkProgram
#undef glPixelStorei
#undef glShaderSource
#undef glTexImage2D
#undef glTexParameteri
#undef glUniform1i
#undef glUniform2f
#undef glUniformMatrix4fv
#undef glUseProgram
#undef glVertexAttribIPointer
#undef glVertexAttribPointer

// clang-format off
#define glActiveTexture			(void)sizeof
#define glAttachShader			(void)sizeof
#define glBindBuffer			(void)sizeof
#define glBindFragDataLocation		(void)sizeof
#define glBindTexture			(void)sizeof
#define glBindVertexArray		(void)sizeof
#define glBufferData			(void)sizeof
#define glCompileShader			(void)sizeof
#define glCreateProgram()               0
#define glCreateShader			0;(void)sizeof
#define glDeleteBuffers			(void)sizeof
#define glDeleteProgram			(void)sizeof
#define glDeleteShader			(void)sizeof
#define glDeleteTextures		(void)sizeof
#define glDeleteVertexArrays		(void)sizeof
#define glDrawArrays			(void)sizeof
#define glEnableVertexAttribArray	(void)sizeof
#define glGenBuffers			(void)sizeof
#define glGenTextures			(void)sizeof
#define glGenVertexArrays		(void)sizeof
#define glGetProgramInfoLog		(void)sizeof
#define glGetProgramiv			(void)sizeof
#define glGetShaderInfoLog		(void)sizeof
#define glGetShaderiv			(void)sizeof
#define glGetUniformLocation		0;(void)sizeof
#define glLinkProgram			(void)sizeof
#define glPixelStorei			(void)sizeof
#define glShaderSource			(void)sizeof
#define glTexImage2D			(void)sizeof
#define glTexParameteri			(void)sizeof
#define glUniform1i			(void)sizeof
#define glUniform2f			(void)sizeof
#define glUniformMatrix4fv		(void)sizeof
#define glUseProgram			(void)sizeof
#define glVertexAttribIPointer		(void)sizeof
#define glVertexAttribPointer		(void)sizeof
// clang-format on
