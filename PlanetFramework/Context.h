#pragma once
#include "Scene.h"
#include "Singleton.h"
#include "Time.h"

class Camera;

class ContextObjects {
public:
  ContextObjects() {
  }
  ~ContextObjects() {
  }
  Time *pTime;
  Camera *pCamera;
  Scene *pScene;
};

struct Context : public Singleton<Context>, public ContextObjects {
public:
  Context() : ContextObjects() {
  }
  ~Context() {
  }
  void SetContext(ContextObjects *pContext) {
    pTime = pContext->pTime;
    pCamera = pContext->pCamera;
    pScene = pContext->pScene;
  }
};
