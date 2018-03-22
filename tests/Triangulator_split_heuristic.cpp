#include "Triangulator.h"
#include "utils.h"
#include <algorithm>
#include <iostream>
#include <limits>

#include "Triangulator_split_heuristic.h"

static auto get_name(TriNext v) {
  switch (v) {
  case CULL:
    return "CULL";
  case LEAF:
    return "LEAF";
  case SPLIT:
    return "SPLIT";
  case SPLITCULL:
    return "SPLITCULL";
  default:
    return "Unknown";
  }
}

bool test() {
  using glm::vec3;
  using std::cerr;

  Triangulator tri{nullptr};
  vec3 a{0, 0, 0}, b{2, 0, 0}, c{1, 1, 0};
  // Test no culling
  {
    const auto float_max = std::numeric_limits<float>::max();
    cerr << "Test no culling\n";
    // Set up fake LUT
    // Disable culling
    tri.m_TriLevelDotLUT.emplace_back(float_max);
    tri.m_TriLevelDotLUT.emplace_back(float_max);

    cerr << "  Expected: SPLITCULL\n";
    tri.m_DistanceLUT.emplace_back(float_max);
    auto ret = tri.SplitHeuristic(a, b, c, 0, false);
    cerr << "  Got: " << get_name(ret) << "\n";
    if (ret != TriNext::SPLITCULL) {
      return false;
    }

    cerr << "  Expected: LEAF\n";
    tri.m_DistanceLUT.emplace_back(0);
    ret = tri.SplitHeuristic(a, b, c, 1, false);
    cerr << "  Got: " << get_name(ret) << "\n";
    if (ret != TriNext::LEAF) {
      return false;
    }
  }

  return true;
}
