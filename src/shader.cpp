#include "shader.hpp"
#include <GL/glew.h>
#include <iostream>
#include <fstream>

bool Shader::loadFromFile(const std::string& path, enum Type type){
  std::string src;

  std::ifstream in(path.c_str(), std::ios::in);
  if (!in){
    std::cerr << "Could not load shader: file not found. :(\n";
    return false;
  }

  while (!in.eof()){
    src.push_back(in.get());
  }
}

bool Shader::loadFromSource(const std::string& source, enum Type type){
  programID = glCreateProgram();

  GLuint shaderID;

  switch(type){
  case Type::Vertex:
    shaderID = glCreateShader(GL_VERTEX_SHADER);
    break;
  case Type::Fragment:
    shaderID = glCreateShader(GL_FRAGMENT_SHADER);
    break;
  default:
    return false;
  }

  glShaderSource(shaderID, 1, source.c_str(), 0);
  glCompileShader(shaderID);

  int compiled;
  glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &compiled);  //Get errors
  if (compiled){
    glAttachShader(programID, shaderID);
    return false;
  } else {
    std::cerr << []() {
      switch (type){
        case Type::Vertex:
            return "Could not compile Vertex Shader. :(";
          break;
        case Type::Fragment:
            return "Could not compile Fragment shader. :(";
          break;
        default:
          return "Unknow error. :(";
      }
    } << '\n';
    return false;
  }
}
