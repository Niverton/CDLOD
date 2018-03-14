#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <memory>

#include <chrono>

template <typename Fun>
double Timer(Fun f, int nb){
  auto s = std::chrono::system_clock::now();
  
  f(nb);
  
  auto e = std::chrono::system_clock::now();
  auto elapse = std::chrono::duration<double, std::milli>(e - s);

  return elapse.count();
}

void usage(char* msg){
  std::cerr << "Usage: " << msg << " <nb_iter_inf> <nb_iter_sup>\n";
  std::exit(-1);
}

int main(int argc, char** argv){
  if (argc != 3)  usage(argv[0]);

  int nb_iter_inf = atoi(argv[1]);
  int nb_iter_sup = atoi(argv[2]);

  std::cout << "CSV format - footstep : 2^{min..max}\n";

  {
    std::cout << "Simplex (ms); ";
    for (int i=nb_iter_inf; i<nb_iter_sup; i++){
      int nb = pow(2, i);
      double time =Timer([](long unsigned int nb)
      {
        std::vector<glm::vec3> vertices {nb, glm::vec3{0.0, 0.0, 0.0}};
        for (auto v: vertices){
          v *= glm::simplex(v);
        }
      }, nb);
      std::cout << time << "; ";
    }
    std::cout << '\n';
  }

  {
    std::cout << "Perlin (ms); ";
    for (int i=nb_iter_inf; i<nb_iter_sup; i++){
      int nb = pow(2, i);
      double time =Timer([](long unsigned int nb)
      {
        std::vector<glm::vec3> vertices {nb, glm::vec3{0.0, 0.0, 0.0}};
        for (auto v: vertices){
          v *= glm::perlin(v);
        }
      }, nb);
      std::cout << time << "; ";
    }
    std::cout << '\n';
  }
}
