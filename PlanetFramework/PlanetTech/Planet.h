#pragma once

class Patch;  // lines 8-8
class Texture;  // lines 6-6
class Transform;  // lines 4-4
class Triangulator;  // lines 7-7

class Planet {
public:
  Planet();
  virtual ~Planet();

  void Init();
  void Update();
  void Draw();
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
