#pragma once

#if PLATFORM_Win
#include <glm\glm.hpp>
#else
#include <glm/glm.hpp>
#endif

#include "InputManager.h" // for InputManager
#include "PlanetTech/Planet.h"       // for Planet
#include "Settings.h"     // for Settings::WindowSettings
#include "Time.h"         // for Time
#include "Transform.h"    // for Transform
#include "utils.h"       // for INPUT, TIME, WINDOW
#include <SDL2/SDL_scancode.h> // for ::SDL_SCANCODE_KP_4
#include <cmath>          // for powf, cos, sin, sqrtf

/*!
  \brief  Camera provide two mode, orthigraphic and perspective.
          The position of the camera is calculate with longitute, latitute and
          altitude coordinate system.
*/
class Camera {
public:
  Camera();
  ~Camera();

  void SetFieldOfView(float fov) {
    m_FOV = fov;
  }
  void SetOrthoSize(float size) {
    m_Size = size;
  }
  void SetNearClippingPlane(float nearPlane) {
    m_NearPlane = nearPlane;
  }
  void SetFarClippingPlane(float farPlane) {
    m_FarPlane = farPlane;
  }

  float GetFOV() const {
    return m_FOV;
  }
  float GetNearPlane() const {
    return m_NearPlane;
  }
  float GetFarPlane() const {
    return m_FarPlane;
  }

  void UsePerspectiveProjection() {
    m_PerspectiveProjection = true;
  }
  void UseOrthographicProjection() {
    m_PerspectiveProjection = false;
  }

  /*!
    \brief  This function update camera stuff according to keyboard ans mouse 
            input.
            New far and near plane are calculate based on planet: 
            $ 
              \sqrt{(radius + altitude}^{2} - radius^{2}} +
              \sqrt{(radius + max_height}^{2} - radius^{2}}
            $

            Projection matrix and other matrix has calculate thanks to 
            the class Transform.
  */
  void Update();

  glm::mat4 GetView() const {
    return m_View;
  }
  glm::mat4 GetProj() const {
    return m_Projection;
  }
  glm::mat4 GetViewInv() const {
    return m_ViewInverse;
  }
  glm::mat4 GetViewProj() const {
    return m_ViewProjection;
  }
  glm::mat4 GetViewProjInv() const {
    return m_ViewProjectionInverse;
  }

  // Movement stuff
  void SetPlanet(Planet *pPlanet) {
    m_pPlanet = pPlanet;
  }
  bool HasMoved() const {
    return m_Moved;
  }
  Transform *GetTransform() {
    return m_pTransform;
  }

  float GetAltitude() const {
    return m_Altitude;
  }

private:
  // Movement stuff

  Planet *m_pPlanet = nullptr;
  float m_Altitude = 10000;
  float m_Latitude = 0;
  float m_Longitude = 0;
  float m_RotationSpeed = 0.5f;
  Transform *m_pTransform = nullptr;
  bool m_Moved = true;

  // Camera projection
  glm::mat4 m_View, m_Projection, m_ViewInverse, m_ViewProjection,
      m_ViewProjectionInverse;
  float m_FarPlane = 200000;
  float m_NearPlane = 1;
  float m_FOV = 45.f;
  float m_Size = 25.f;
  bool m_PerspectiveProjection = true;
};
