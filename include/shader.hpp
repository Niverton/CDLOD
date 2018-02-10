#pragma once

#include <GL/gl.h>
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

private:
  GLuint programID;
};
