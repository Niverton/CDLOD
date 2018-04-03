#include <chrono>
#include <iostream>
#include "Planet.h"
#include "Types/Procedural.h"
#include "utils.h"
#include <functional>
#include <memory>
#include <cmath>
#include <vector>

/*
    \brief    Use for compute elapse time of function Fun
    \param    Lambda function
    \param    Arg1, use for specifie the size of the texture 
    \param    Arg2, pointer to a planet
    \return   Elsape time
 */
template <typename Fun>
double Timer(Fun f, int nb){
  auto s = std::chrono::system_clock::now();
  
  f(nb);
  
  auto e = std::chrono::system_clock::now();
  auto elapse = std::chrono::duration<double, std::milli>(e - s);

  return elapse.count();

}

bool test(){
  
  auto simplex = [] (int i) {
              ProceduralPlanet::Properties prop;
              prop.width = prop.height = pow(2, i);
              prop.noise = ProceduralPlanet::Noise::SIMPLEX;
              
              Planet* p = new ProceduralPlanet (&prop);
            };
  
  auto ridged = [] (int i) {
              ProceduralPlanet::Properties prop;
              prop.width = prop.height = pow(2, i);
              prop.noise = ProceduralPlanet::Noise::RIDGED_NOISE;
              
              Planet* p = new ProceduralPlanet (&prop);
  	    };

  auto flow = [] (int i) {
              FlowNoiseProperties prop;
              prop.width = prop.height = pow(2, i);
              prop.noise = ProceduralPlanet::Noise::FLOW_NOISE;
              
              Planet* p = new ProceduralPlanet (&prop);
            };

  auto fbm = [] (int i) {
              FbmProperties prop;
              prop.width = prop.height = pow(2, i);
              prop.noise = ProceduralPlanet::Noise::FBM;
              
              Planet* p = new ProceduralPlanet (&prop);
	   };

  auto warped = [] (int i) {
              FbmProperties prop;
              prop.width = prop.height = pow(2, i);
              prop.noise = ProceduralPlanet::Noise::WARPED_FBM;
              
              Planet* p = new ProceduralPlanet (&prop);
           };

  auto dfbm = [] (int i) {
              FbmProperties prop;
              prop.width = prop.height = pow(2, i);
              prop.noise = ProceduralPlanet::Noise::DFBM_WARPED_FBM;
              
              Planet* p = new ProceduralPlanet (&prop);
            };

  auto fractal = [] (int i) {
              RidgedMultiFractalVariationProperties prop;
              prop.width = prop.height = pow(2, i);
      	      prop.noise = ProceduralPlanet::Noise::RIDGED_MULTI_FRACTAL_VARIATION;

              Planet* p = new ProceduralPlanet (&prop);
  	    };

  std::cout << "SIMPLEX;RIDGED;FLOW;FBM;WARPED;DFBM;FRACTAL;\n";
  //[6..12] -> [64x64 .. 4096x4096]
  static const int nb_tests = 6;
  for (int i=6; i < 6 + nb_tests; i++){
    std::cout << Timer(simplex, i)  << ';';
    std::cout << Timer(ridged, i)   << ';';
    std::cout << Timer(flow, i)     << ';';
    std::cout << Timer(fbm, i)      << ';';
    std::cout << Timer(warped, i)   << ';';
    std::cout << Timer(dfbm, i)     << ';';
    std::cout << Timer(fractal, i)  << ';';
    std::cout << '\n';
  }

  return true;
}
