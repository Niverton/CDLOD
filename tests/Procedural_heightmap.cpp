#include "Procedural_heightmap.h"
#include <glm/glm.hpp>
#include <IL/il.h>  
#include <IL/ilu.h> 

#define HEIGHT 1080
#define WIDTH 1920

bool test() {
  iluInit();

  ILuint heightmap = 0;
  ilGenImage(WIDTH * HEIGHT, &heightmap);

  return true;
}
