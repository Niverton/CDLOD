#include "Procedural_heightmap.h"
#include <glm/glm.hpp>
#include <IL/il.h>  
#include <glm/gtc/noise.hpp>
#include <IL/ilu.h> 

#include <vector>

#define WIDTH 1920
#define HEIGHT 1080


bool test() {
  iluInit();

  ILuint heightmap = 0;
  ilGenImages(1, &heightmap);
  ilBindImage(heightmap);

  std::vector<float> z;

  for (int j=0; j<HEIGHT; j++){
    for (int i=0; i<WIDTH; i++){
      z.push_back(glm::simplex(glm::vec3(i, j, 0.0)));
      ilSetPixels(i, j, 1, 1, 1, 1, IL_RGB, IL_FLOAT, &z[i+j]);
      if (ilGetError() != IL_NO_ERROR)  return false;
    }
  }
 
  ilSave(IL_RGB, "test.png");
  return true;
}
