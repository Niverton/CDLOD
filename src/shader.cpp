#include "shader.hpp"
#include <GL/glew.h>
#include <iostream>
#include <fstream>

bool Shader::is_linked = false;

Shader::Shader(){
  program_ID = glCreateProgram();
}

Shader::~Shader(){

}

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
    glAttachShader(program_ID, shaderID);
    shaders_ID.push_back(shaderID);
    return true;
  } else {
    char info[512];
    glGetShaderInfoLog(shaderID, 512, NULL, info);

    std::cerr <<  [](enum Type t) {
      switch (t){
        case Type::VERTEX:
            return "Could not compile Vertex Shader";
          break;
        case Type::FRAGMENT:
            return "Could not compile Fragment shader";
          break;
        default:
          return "Unknow error :(";
      }
    } << ": " << info << '\n';
    return false;
  }
}

void Shader::activate() const {
  glUseProgram(program_ID);
}

void Shader::deactivate() const {
  glUseProgram(0);
}

GLint Shader::getAttribLocation(const std::string& name) const {
  return glGetAttribLocation(program_ID, name.c_str());
}

GLint Shader::getUniformLocation(const std::string& name) const {
  return glGetUniformLocation(program_ID, name.c_str());
}

bool Shader::link(){
  if (!is_linked){
    glLinkProgram(program_ID);
    GLint status;
    glGetProgramiv(program_ID, GL_LINK_STATUS, &status);
    if (!status) {
      char info[512];  
      glGetProgramInfoLog(program_ID, 512, NULL, info);
      std::cerr << "Error: could not link shader program: \n" << info << '\n';
    }
    for (GLuint shader : shaders_ID){
      glDeleteShader(shader);
    }
    is_linked = true;
    return true;
  }
  return false;
}
