#include "terrain.hpp"
#include "sphere_mesh.hpp"
#include <iostream>

Terrain::Terrain(float sphere_radius, int sphere_density){
  bool vert_status, frag_status, link_status;
  vert_status = shader.loadFromFile("shaders/terrain.vert", Shader::Type::VERTEX);
  frag_status = shader.loadFromFile("shaders/terrain.frag", Shader::Type::FRAGMENT);
  link_status = shader.link();
  
  if (!vert_status || !frag_status || !link_status){
     throw "Error: could not create shader.";
  }
  
  SphereMesh sphere_generator(sphere_radius, sphere_density);
  
  vertices = sphere_generator.getVertices();
  faces = sphere_generator.getFaces();
  
  std::cout << "Vertices count: "<< vertices.size() << '\n';
  std::cout << "Faces count: "<< faces.size() << '\n';
  
  
  /*
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
  */
  
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

void Terrain::draw(){
  shader.activate();
  
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glDepthFunc(GL_LESS);

  glBindVertexArray(vertex_array_ID);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_ID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_ID);

  int vertex_location = shader.getAttribLocation("a_pos");
  glVertexAttribPointer(
    vertex_location,
    3,                        //vec3
    GL_FLOAT,
    GL_FALSE,
    sizeof(type::Vertex),
    0);                       //stride

  glEnableVertexAttribArray(vertex_location);
  glDrawElements(GL_TRIANGLES, 3*faces.size(), GL_UNSIGNED_INT, 0);
 //glDrawArrays(GL_TRIANGLES, 0, vertices.size());

  glDisableVertexAttribArray(vertex_location);
  
  shader.deactivate();
}
