#pragma once

#include <GL/glew.h>
#include <string>

class Shader{
public:
  enum class Type{
    VERTEX,
    FRAGMENT,
  };

  bool loadFromFile(const std::string& path, enum Type type);
  bool loadFromSource(const std::string& source, enum Type type);

  void activate() const;
  void deactivate() const;
  
  GLint getAttribLocation(const std::string& name) const;
  GLint getUniformLocation(const std::string& name) const;

private:
  bool is_valide = false;
  GLuint programID;
};
