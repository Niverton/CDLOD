#pragma once

#include "Patch.h" // for PatchInstance
#include <vector>  // for vector
#if PLATFORM_Win
#include <glm\glm.hpp>
#else
#include <glm/glm.hpp>
#endif

class Frustum; // lines 3-3
class Planet;  // lines 4-4

enum class TriNext { CULL, LEAF, SPLIT, SPLITCULL };

/**
  \brief  This was the represention of a node in a quadtree.
          A node store a single triangle reprensent by 3 vertices.
          Other data was conserved in each node such as an information
          about the statement of the node.
          The node also had a pointer to this parent to allow deplacement
          from top to bottom and vice versa.
          Now, this struct is used for convenience to store the first triangles
          of the Icosahedron

*/
struct Tri {
  Tri(glm::vec3 A, glm::vec3 B, glm::vec3 C, Tri *Parent, short Level)
      : parent(Parent), level(Level), a(A), b(B), c(C) {
  }

  Tri *parent = nullptr;

  Tri *c1 = nullptr;
  Tri *c2 = nullptr;
  Tri *c3 = nullptr;
  Tri *c4 = nullptr;

  TriNext state{TriNext::CULL};

  short level;

  glm::vec3 a;
  glm::vec3 b;
  glm::vec3 c;
};

/**
  \brief  Class triangulator recursively construct the base of the mesh.
          The recursion start from 20 triangles forming an icosahedron.
          It then break those sufficently close into smaller triangles, in order
  to focus precision and computation on the closest parts of the planet.

          */

class Triangulator {
public:
  Triangulator(Planet *pPlanet);
  ~Triangulator();

  /**
    \Brief  Initialize the triangulator.
            Create the first 20 faces of the icasahedron,
            Initialize the frustum and precompute culling.
  */
  void Init();

  /**
    \brief  Update geometrie according to keyboard input (max level change,
    frustum locked...). The level of detail drawn can be forced. Default level
    is 15.
  */
  bool Update();

  /**
    \brief  Calculate distanceLUT base on FOV/AllowedTriPx. The distance table
    is heuristically calculated to obtain a smooth precision variation. The
    distanceLut should not be recalculated each time and instead done once in
    precalculate. For each triangle in icosahedron, call RecursiveTriangle.
  */
  void GenerateGeometry();

  bool IsFrustumLocked() const {
    return m_LockFrustum;
  }
  Frustum *GetFrustum() {
    return m_pFrustum;
  }
  int GetVertexCount() const {
    return m_Positions.size();
  }

private:
  friend class Planet;
#if defined(test_triangulator_split_heuristic) ||                              \
    defined(test_triangulator_recursive_triangle)
  friend bool test();
#endif
  /**
      \brief
      Calculate some level dependent values, used later in the culling process,
     to know whether or not we can cull a triangle in the recursion.

      */
  void Precalculate();

  /**
    \brief
    \param  a, first vertex of triangle
    \param  b, second vertex of triangle
    \param  c, third vertex of triangle
    \param  level, the level of the current triangle in the quadtree
    \param  frustrumCull  enable/disable the frustum culling
    \return Enumeration specifying what we need to do whit the target:
              SPLITCULL if the target need to be split
              SPLIT if the target need to be split without checking frustrum
    culling LEAF if the target is to far to be split again CULL if the traget is
    outside of the frustum or facing the bad direction
  */
  TriNext SplitHeuristic(glm::vec3 &a, glm::vec3 &b, glm::vec3 &c, short level,
                         bool frustumCull);

  /**
    \brief  Build recursively the mesh:
    Take a triangle, and threat it  accordingly to the result of splitHeuristic.
    If it need to be split, lunch the recursion over 4 new triangles.
    Theses triangles are those formed by the centers of each edges. See this
    image :https://goo.gl/images/3DrWmc If it's culled, dont do anything. If
    it's a leaf, put it in the buffer

    \param  a, first vertex of triangle
    \param  b, second vertex of triangle
    \param  c, third vertex of triangle
    \param  level, the level of the current triangle in the quadtree
    \param  frustrumCull  enable/disable the frustum culling
  */
  void RecursiveTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, short level,
                         bool frustumCull);

  // Triangulation paramenters
  float m_AllowedTriPx = 300.f;
  int m_MaxLevel = 15;

  std::vector<Tri> m_Icosahedron;

  /**
    \brief  Lut used by SplitHeursitic to know the distances at which point it
    should not split anymore.
  */
  std::vector<float> m_DistanceLUT;
  std::vector<float> m_TriLevelDotLUT;
  std::vector<float> m_HeightMultLUT;

  std::vector<Tri *> m_Leafs;

  Planet *m_pPlanet = nullptr;
  Frustum *m_pFrustum = nullptr;
  bool m_LockFrustum = false;

  std::vector<PatchInstance> m_Positions;
};
