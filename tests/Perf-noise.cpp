#include <chrono>
#include <iostream>
#include "Planet.h"
#include "Types/Procedural.h"
#include "utils.h"
#include <cmath>

/*
    \brief    Use for compute elapse time of function Fun
    \param    Lambda function
    \param    Arg1, use for specifie the size of the texture 
    \param    Arg2, pointer to a planet
    \return   Elsape time
 */
template <typename Fun>
double Timer(Fun f, int nb, int type){
  auto s = std::chrono::system_clock::now();
  
  f(nb, type);
  
  auto e = std::chrono::system_clock::now();
  auto elapse = std::chrono::duration<double, std::milli>(e - s);

  return elapse.count();

}

bool test(){
  auto noise = [] (int i, int j) {
              ProceduralPlanet::Properties prop;
              prop.width = pow(2, i);
              prop.height = pow(2, i);
              prop.noise = static_cast<ProceduralPlanet::Noise> (j);

              ProceduralPlanet p {&prop};
           };

  std::cout << "simplex;perlin;ridged;flow;fbm;warped;dfbm;fractal;\n";
  //[6..11] -> [64x64 .. 2048x2048]
  static const int nb_tests = 5;
  for (int i=6; i <= 6 + nb_tests; i++){


    for (int j=0; j<8; j++){
      std::cout << Timer(noise, i, j)  << ';';
    }
    std::cout << '\n';
  }

  return true;
}
