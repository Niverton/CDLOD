#include "terrain.hpp"

Terrain::Terrain(){

  /* Create buffer for vertices */
  glGenBuffers(1, &vertex_buffer_ID);
  if (!(glGetError() != GL_NO_ERROR)){
    throw "Error: could not generate OpenGL vertex buffer.\n";
  }

  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_ID);
  glBufferData(
    GL_ARRAY_BUFFER,
    sizeof(type::Vertex) * vertices.size(),
    static_cast<void*>(&vertices[0].position[0]),
    GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  /* create buffer for faces */
  glGenBuffers(1, &index_buffer_ID);
  if (!(glGetError() != GL_NO_ERROR)){
    throw "Error: could not generate OpenGL index buffer.\n";
  }
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_ID);
  glBufferData(
    GL_ELEMENT_ARRAY_BUFFER,
    sizeof(type::Face) * faces.size(),
    static_cast<void*>(&faces[0]),
    GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glGenVertexArrays(1, &vertex_array_ID);
  if (!(glGetError() != GL_NO_ERROR)){
    throw "Error: could not generate OpenGL vertex array.\n";
  }
}

Terrain::~Terrain(){
  glDeleteBuffers(1, &vertex_buffer_ID);
  glDeleteBuffers(1, &index_buffer_ID);
}

void Terrain::draw(const Shader& shader){
  glBindVertexArray(vertex_array_ID);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_ID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_ID);

  int vertex_location = shader.getAttribLocation("a_pos");
  glVertexAttribPointer(
    vertex_location,
    4,                        //vec4
    GL_FLOAT,
    GL_FALSE,
    sizeof(type::Vertex),
    0);                       //stride

  glEnableVertexAttribArray(vertex_location);
  glDrawElements(GL_TRIANGLES, 3*faces.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(vertex_location);
}
