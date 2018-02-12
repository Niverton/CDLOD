#pragma once

#include <GL/glew.h>
#include <string>
#include <vector>

class Shader{
public:
  enum class Type{
    VERTEX,
    FRAGMENT,
  };
  Shader();
  ~Shader();

  bool loadFromFile(const std::string& path, enum Type type);
  bool loadFromSource(const std::string& source, enum Type type);
  bool link();

  void activate() const;
  void deactivate() const;
  
  GLint getAttribLocation(const std::string& name) const;
  GLint getUniformLocation(const std::string& name) const;

private:
  bool is_valide = false;
  GLuint program_ID;
  std::vector<GLuint> shaders_ID;

  
  static bool is_linked;
};

