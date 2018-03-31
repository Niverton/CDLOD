#pragma once

#ifdef PLATFORM_Win
#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#else
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#endif

class Transform {
public:
  Transform() = default;

  void UpdateTransforms();

  void SetPosition(glm::vec3 pos) {
    m_Position = pos;
  }
  void SetPosition(float x, float y, float z) {
    m_Position = glm::vec3(x, y, z);
  }
  void Translate(glm::vec3 translation) {
    m_Position += translation;
  }
  void SetRotation(glm::quat rot) {
    m_Rotation = rot;
  }
  void SetRotation(glm::vec3 euler) {
    m_Rotation = glm::quat(euler);
  }
  void Rotate(glm::quat rot) {
    m_Rotation *= rot;
  }
  void Rotate(glm::vec3 euler) {
    m_Rotation *= glm::quat(euler);
  }
  void SetScale(glm::vec3 scale) {
    m_Scale = scale;
  }
  void Scale(glm::vec3 scale) {
    m_Scale *= scale;
  }

  const glm::mat4 &GetTransform() const {
    return m_Tranform;
  }
  const glm::vec3 &GetPosition() const {
    return m_Position;
  }
  const glm::quat &GetRotation() const {
    return m_Rotation;
  }
  const glm::vec3 &GetScale() const {
    return m_Scale;
  }

  const glm::vec3 &GetForward() const {
    return m_Forward;
  }
  const glm::vec3 &GetUp() const {
    return m_Up;
  }
  const glm::vec3 &GetRight() const {
    return m_Right;
  }

private:
  glm::mat4 m_Tranform{1.0f};

  glm::vec3 m_Position{0.f, 0.f, 0.f};
  glm::quat m_Rotation{};
  glm::vec3 m_Scale{1.f, 1.f, 1.1f};

  glm::vec3 m_Forward{0.f, 0.f, 1.f};
  glm::vec3 m_Right{1.f, 0.f, 0.f};
  glm::vec3 m_Up{0.f, 1.f, 0.f};
};
