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

  return loadFromSource(src, type);
}

bool Shader::loadFromSource(const std::string& source, enum Type type){
  programID = glCreateProgram();

  GLuint shaderID;

  switch(type){
  case Type::VERTEX:
    shaderID = glCreateShader(GL_VERTEX_SHADER);
    break;
  case Type::FRAGMENT:
    shaderID = glCreateShader(GL_FRAGMENT_SHADER);
    break;
  default:
    return false;
  }

  const GLchar* src = source.c_str();
  glShaderSource(shaderID, 1, static_cast<const GLchar**>(&src), 0);
  glCompileShader(shaderID);

  int compiled;
  glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);  //Get errors
  if (compiled){
    glAttachShader(programID, shaderID);
   
    glLinkProgram(programID);
    GLint status;
    glGetProgramiv(programID, GL_LINK_STATUS, &status);
    is_valide = (bool) status;
    
    return true;
  } else {
    std::cerr << [](enum Type t) {
      switch (t){
        case Type::VERTEX:
            return "Could not compile Vertex Shader. :(";
          break;
        case Type::FRAGMENT:
            return "Could not compile Fragment shader. :(";
          break;
        default:
          return "Unknow error. :(";
      }
    } << '\n';
    return false;
  }
}

void Shader::activate() const {
  glUseProgram(programID);
}

void Shader::deactivate() const {
  glUseProgram(0);
}

GLint Shader::getAttribLocation(const std::string& name) const {
  return glGetAttribLocation(programID, name.c_str());
}

GLint Shader::getUniformLocation(const std::string& name) const {
  return glGetUniformLocation(programID, name.c_str());
}
