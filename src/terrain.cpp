#include "terrain.hpp"
#include "sphere_mesh.hpp"

Terrain::Terrain(){
  /*
  SphereMesh sphere_generator(0.4, 10);
  
  vertices = sphere_generator.getVertices();
  faces = sphere_generator.getFaces();
  */
  
  type::Vertex v1;
  type::Vertex v2;
  type::Vertex v3;

  v1.position = type::Vec3(-0.5, -0.5, 0);
  v2.position = type::Vec3(0.5, -0.5, 0);
  v3.position = type::Vec3(0.5, 0.5, 0);

  vertices.push_back(v1);
  vertices.push_back(v2);
  vertices.push_back(v3);

  type::Face f1(0, 1, 2);
  faces.push_back(f1);

  /* Create buffer for vertices */
  glGenBuffers(1, &vertex_buffer_ID);
  if (!(glGetError() == GL_NO_ERROR)){
    throw "Error: could not generate OpenGL vertex buffer.\n";
  }

  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_ID);
  glBufferData(
    GL_ARRAY_BUFFER,
    sizeof(type::Vertex) * vertices.size(),
    static_cast<void*>(&vertices[0].position[0]),
    GL_DYNAMIC_DRAW);
  if (!(glGetError() == GL_NO_ERROR)){
    throw "Error: could not send vertex data to GC.\n";
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  /* create buffer for faces */
  glGenBuffers(1, &index_buffer_ID);
  if (!(glGetError() == GL_NO_ERROR)){
    throw "Error: could not generate OpenGL index buffer.\n";
  }
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_ID);
  glBufferData(
    GL_ELEMENT_ARRAY_BUFFER,
    sizeof(type::Face) * faces.size(),
    static_cast<void*>(&faces[0]),
    GL_STATIC_DRAW);
  if (!(glGetError() == GL_NO_ERROR)){
    throw "Error: could not send index data to GC.\n";
  }
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glGenVertexArrays(1, &vertex_array_ID);
  if (!(glGetError() == GL_NO_ERROR)){
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
