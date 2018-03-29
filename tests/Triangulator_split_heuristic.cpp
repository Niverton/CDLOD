#include "Triangulator.h"
#include "utils.h"
#include <algorithm>
#include <iostream>
#include <limits>

#include "Triangulator_split_heuristic.h"

static auto get_name(TriNext v) {
  switch (v) {
  case CULL:
    // Returned when the triangle was culled because it was behind the
    // planet
    return "CULL";
  case LEAF:
    // Returned when the triangle is at the correct level of detail
    return "LEAF";
  case SPLIT:
    // The triangle should be split (too high in the quadtree)
    return "SPLIT";
  case SPLITCULL:
    // The triangle should be split and the next calls should be with
    // frustum culling enabled
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
  // Test with no backface or frustum culling
  const auto float_max = std::numeric_limits<float>::max();
  cerr << "Test no culling\n";
  /* Set up fake look up table to disable backface culling
   */
  tri.m_TriLevelDotLUT.emplace_back(float_max);
  tri.m_TriLevelDotLUT.emplace_back(float_max);

  {
    cerr << "  Expected: SPLIT\n";
    // Set this level's split distance to max so we always get a split
    tri.m_DistanceLUT.emplace_back(float_max);
    auto ret = tri.SplitHeuristic(a, b, c, 0, false);
    cerr << "  Got: " << get_name(ret) << "\n";
    if (ret != TriNext::SPLIT) {
      return false;
    }
  }
  {
    cerr << "  Expected: LEAF\n";
    // Set the split distance to 0 so we don't split
    tri.m_DistanceLUT.emplace_back(0);
    auto ret = tri.SplitHeuristic(a, b, c, 1, false);
    cerr << "  Got: " << get_name(ret) << "\n";
    if (ret != TriNext::LEAF) {
      return false;
    }
  }

  return true;
}
