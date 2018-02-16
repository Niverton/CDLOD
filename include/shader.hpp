#pragma once

/*!
 * \file Shader.hpp
 * \brief Use to open and deals with OpenGL shaders  
 */

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

  /*!
   * \brief Load a shader from file if the path is correct and can be load.
   * \param path : path of the file
   * \param type : type of the shader (VERTEX or FRAGMENT)
   * 
   *  \return true if the file can be open & load , false otherwise
   */

  bool loadFromFile(const std::string& path, enum Type type);

    /*!
   * \brief Load a shader from source if the source is correct and can be load.
   * \param source : source of the shader
   * \param type : type of the shader (VERTEX or FRAGMENT)
   * 
   *  \return true if the file can be open & load , false otherwise
   */

  bool loadFromSource(const std::string& source, enum Type type);

  /*!
   * \brief Allows OpenGL to manage shaders. Need to be use after loading all shaders (2 minimum (one VERTEX and one FRAGMENT))
   * \return true if OpenGL correctly link shaders, flase otherwise.
   */
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

