#pragma once

class Shader;
class Transform;
class Frustum;
class Texture;
class Triangulator;
class Patch;

/**
  \brief  Extend this class for create new planet type.
          This class manage all stuff about planet rendering such as 
          texture, triangulator and patch.
*/

class Planet {
public:
  Planet();
  virtual ~Planet();

  /**
    \brief  Load texture data and initialize triangulator and patch.
  */
  void Init();

  /**
    \brief  Regenerate geometry and update position.
  */
  void Update();

  /**
    \brief  Draw planet
  */
  void Draw();

  /**
    \brief  Draw frustum
  */
  void DrawWire();

  float GetRadius() {
    return m_Radius;
  }
  float GetMaxHeight() {
    return m_MaxHeight;
  }
  int GetVertexCount();
  Transform *GetTransform() {
    return m_pTransform;
  }
  Triangulator *GetTriangulator() {
    return m_pTriangulator;
  }

  Texture *GetHeightMap() {
    return m_pHeight;
  }
  Texture *GetDiffuseMap() {
    return m_pDiffuse;
  }
  Texture *GetDetail1Map() {
    return m_pDetail1;
  }
  Texture *GetDetail2Map() {
    return m_pDetail2;
  }
  Texture *GetHeightDetailMap() {
    return m_pHeightDetail;
  }

protected:
  // Planet parameters
  float m_Radius = 1737.1f;
  float m_MaxHeight = 10.7f;

  Texture *m_pDiffuse = nullptr;
  Texture *m_pDetail1 = nullptr;
  Texture *m_pDetail2 = nullptr;
  Texture *m_pHeightDetail = nullptr;
  Texture *m_pHeight = nullptr;

  Transform *m_pTransform = nullptr;

private:
  bool m_Rotate = false;

  // Calculations
  Triangulator *m_pTriangulator = nullptr;
  Patch *m_pPatch = nullptr;
};
