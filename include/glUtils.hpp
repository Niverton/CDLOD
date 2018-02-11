#include <GL/glew.h>

namespace glUtils{

  void callback_error(
    GLenum src, 
    GLenum type, 
    GLuint id, 
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam);

  void initGL();
}
