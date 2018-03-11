#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <memory>

#include <chrono>

template <typename T>
class TestPerf{
public:
  TestPerf(T& t): _list(t) {}
  
  template <typename Fun>

  /**
    \return return duration of f in milli seconds
  */
  double run(Fun f){
    auto s = std::chrono::system_clock::now();
    
    for (auto& i: _list){
      f(i);
    }
    
    auto e = std::chrono::system_clock::now();
    auto elapse = std::chrono::duration<double, std::milli>(e - s);

    return elapse.count();
  }
private:
  T _list;
};


#define SIZE 1000000
int main(int argc, char** argv){
  std::vector<glm::vec3> vertices { SIZE , glm::vec3{0.0, 0.0, 0.0} };

  TestPerf<std::vector<glm::vec3>> test {vertices};

  std::cout << "vertices number: " << SIZE << '\n';

  {
    std::cout << "glm::simplex \t";
    std::cout << "elapse time: " <<
      test.run([](glm::vec3 v) { v *= glm::simplex(v); })
    << " ms\n";
  }

  {
    std::cout << "glm::perlin \t";
    std::cout << "elapse time: " <<
      test.run([](glm::vec3 v) { v *= glm::perlin(v); })
    << " ms\n";
  }


}
