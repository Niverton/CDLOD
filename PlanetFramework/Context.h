#pragma once
#include "Scene.h"
#include "Singleton.h"
#include "Time.h"

#define CONTEXT Context::GetInstance()
#define TIME Context::GetInstance()->pTime
#define SCENE Context::GetInstance()->pScene
#define CAMERA Context::GetInstance()->pCamera

class Camera;

class ContextObjects {
public:
  ContextObjects() {
  }
  ~ContextObjects() {
  }
  Time *pTime = nullptr;
  Camera *pCamera = nullptr;
  Scene *pScene = nullptr;
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
