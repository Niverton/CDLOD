#pragma once

#include <GL/glew.h>
#include <vector>
#include <type.hpp>
#include <shader.hpp>

class Mesh{
public:
  virtual ~Mesh(){};

  virtual void draw(const Shader& shader) = 0;
protected:
  
  std::vector<type::Vertex> vertices;
  std::vector<type::Face> faces;

  GLuint vertex_array_ID;
  GLuint vertex_buffer_ID;
  GLuint index_buffer_ID;
};
