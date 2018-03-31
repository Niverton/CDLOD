#pragma once

class Time;
class Camera;
class ContextObjects;

class SpriteFont;

class Planet;

class Scene {
public:
  Scene(int argc, char** argv);
  ~Scene();

  void Init();

  void Update();

  void Draw();
  void PostDraw();

private:
  // Context
  Time *m_pTime = nullptr;
  Camera *m_pCamera = nullptr;
  ContextObjects *m_pConObj = nullptr;

  // Rendering
  enum RenderMode { SOLID, WIREFRAME, OVERLAY } renderMode = OVERLAY;
  bool m_DrawUI = true;

  SpriteFont *m_pDebugFont = nullptr;

  // Planet tech
  Planet *m_pPlanet;

  //Planet properties
  /**
    \brief if val == cmp then val is set to default value def
  */
  template <typename T>
  void check_value(T& val, T cmp, T def){
    if (val == cmp){
      val = def;
    }
  }
};
