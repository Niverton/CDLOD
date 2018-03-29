#include "PlanetTech/Planet.h"
#include "Triangulator.h"
#include "utils.h"
#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>

#include "Triangulator_recursive_triangle.h"

static std::ostream &operator<<(std::ostream &o, const glm::vec3 &v) {
  std::stringstream ss;
  ss << "{ " << v.x << ", " << v.y << ", " << v.z << " }";
  o << ss.str();
  return o;
}

bool test() {
  using glm::vec3;
  using std::cerr;
  Planet planet{};
  Triangulator tri{&planet};
  vec3 a{0, 0, 0}, b{2, 0, 0}, c{1, 1, 0};

  // Empty positions
  tri.m_Positions.clear();

  // Disable culling
  const auto float_max = std::numeric_limits<float>::max();
  tri.m_TriLevelDotLUT.resize(15);
  std::fill(std::begin(tri.m_TriLevelDotLUT), std::end(tri.m_TriLevelDotLUT),
            float_max);
  tri.m_HeightMultLUT.resize(15);

  cerr << a << ", " << b << ", " << c << "\n";

  auto lamb = [&](int s_count, int level) {
    cerr << "Expected: " << s_count << " splits\n";
    // Empty positions
    tri.m_Positions.clear();
    tri.RecursiveTriangle(a, b, c, level, false);

    cerr << "Got:\n";
    int i = 0;
    for (const auto &t : tri.m_Positions) {
      cerr << t.a << ", " << t.r << ", " << t.s << "\n";
      i++;
    }
    int expected_count = 1 + s_count * 4;
    if (i != expected_count) {
      cerr << "Unexpect triangle number. Expected " << expected_count << ", got " << i
           << "\n";
      return false;
    }

    return true;
  };

  tri.m_DistanceLUT.emplace_back(0);
  lamb(0, 0);

  tri.m_DistanceLUT[0] = 1;
  lamb(1, 0);

  return true;
}
