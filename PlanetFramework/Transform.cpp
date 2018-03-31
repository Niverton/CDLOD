#include "Transform.h"
#include "utils.h"

#include <glm/gtc/matrix_transform.inl> // for scale, translate
#include <glm/gtx/quaternion.hpp>       // for toMat4
#include <glm/gtx/transform.inl>        // for scale, translate

#if PLATFORM_Win
#include <glm\glm.hpp>
#else
#include <glm/glm.hpp>
#endif

void Transform::UpdateTransforms() {
  m_Tranform = glm::translate(m_Position) * glm::toMat4(m_Rotation) *
               glm::scale(m_Scale);

  m_Forward = glm::normalize(m_Rotation * glm::vec3(0, 0, 1));
  m_Right = glm::normalize(m_Rotation * glm::vec3(1, 0, 0));
  m_Up = glm::normalize(glm::cross(m_Forward, m_Right));
}

