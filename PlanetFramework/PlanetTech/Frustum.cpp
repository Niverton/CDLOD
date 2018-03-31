#include "Frustum.h"
#include "Camera.h" // for Camera
#include "Context.h"
#include "Settings.h"  // for Settings::WindowSettings
#include "Shader.h"    // for Shader
#include "Transform.h" // for Transform
#include "utils.h"     // for SafeDelete, WINDOW, CAMERA
#include <cmath>       // for tan
#include <string>      // for string
#if PLATFORM_Win
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#else
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif

Frustum::Frustum() {
  m_pWireShader = new Shader("./Shaders/wire.glsl");
}

void Frustum::Init() {
  // Handle planet material
  m_pWireShader->Build();
  glUseProgram(m_pWireShader->GetProgram());
  m_uModelWire = glGetUniformLocation(m_pWireShader->GetProgram(), "model");
  m_uViewProjWire =
      glGetUniformLocation(m_pWireShader->GetProgram(), "viewProj");
  glUniform1i(glGetUniformLocation(m_pWireShader->GetProgram(), "texHeight"),
              1);

  glGenVertexArrays(1, &m_VAO);
  glGenBuffers(1, &m_VBO);
  glBindVertexArray(m_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, m_Corners.size() * sizeof(glm::vec3),
               m_Corners.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3),
                        (GLvoid *)nullptr);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

// create transforms to prevent transforming every triangle into world space
void Frustum::SetCullTransform(glm::mat4 objectWorld) {
  m_CullWorld = objectWorld;
  m_CullInverse = glm::inverse(objectWorld);
}

void Frustum::SetToCamera(Camera *pCamera) {
  m_Position = pCamera->GetTransform()->GetPosition();
  m_Forward = pCamera->GetTransform()->GetForward();
  m_Up = pCamera->GetTransform()->GetUp();
  m_Right = pCamera->GetTransform()->GetRight();
  m_NearPlane = pCamera->GetNearPlane();
  m_FarPlane = pCamera->GetFarPlane();
  m_FOV = pCamera->GetFOV();
}

void Frustum::Update() {
  // calculate generalized relative width and aspect ratio
  float normHalfWidth = tan(glm::radians(m_FOV));
  float aspectRatio = float(WINDOW.Width) / float(WINDOW.Height);

  // calculate width and height for near and far plane
  float nearHW = normHalfWidth * m_NearPlane;
  float nearHH = nearHW / aspectRatio;
  float farHW = normHalfWidth * m_FarPlane * 0.5f;
  float farHH = farHW / aspectRatio;

  // calculate near and far plane centers
  auto nCenter = m_Position + m_Forward * m_NearPlane;
  auto fCenter = m_Position + m_Forward * m_FarPlane * 0.5f;

  // construct corners of the near plane in the culled objects world space
  auto na = glm::vec3(m_CullInverse *
                      glm::vec4(nCenter + m_Up * nearHH - m_Right * nearHW, 0));
  auto nb = glm::vec3(m_CullInverse *
                      glm::vec4(nCenter + m_Up * nearHH + m_Right * nearHW, 0));
  auto nc = glm::vec3(m_CullInverse *
                      glm::vec4(nCenter - m_Up * nearHH - m_Right * nearHW, 0));
  auto nd = glm::vec3(m_CullInverse *
                      glm::vec4(nCenter - m_Up * nearHH + m_Right * nearHW, 0));
  // construct corners of the far plane
  auto fa = glm::vec3(m_CullInverse *
                      glm::vec4(fCenter + m_Up * farHH - m_Right * farHW, 0));
  auto fb = glm::vec3(m_CullInverse *
                      glm::vec4(fCenter + m_Up * farHH + m_Right * farHW, 0));
  auto fc = glm::vec3(m_CullInverse *
                      glm::vec4(fCenter - m_Up * farHH - m_Right * farHW, 0));
  auto fd = glm::vec3(m_CullInverse *
                      glm::vec4(fCenter - m_Up * farHH + m_Right * farHW, 0));

  m_PositionObject = glm::vec3(m_CullInverse * glm::vec4(m_Position, 0));
  m_RadInvFOV = 1 / glm::radians(m_FOV);

  // construct planes
  m_Planes.clear();
  // winding in an outside perspective so the cross product creates normals
  // pointing inward
  m_Planes.emplace_back(na, nb, nc); // Near
  // m_Planes.push_back(Plane(fb, fa, fd));//Far Maybe skip this step? most
  // polys further away should already be low res
  m_Planes.emplace_back(fa, na, fc); // Left
  m_Planes.emplace_back(nb, fb, nd); // Right
  m_Planes.emplace_back(fa, fb, na); // Top
  m_Planes.emplace_back(nc, nd, fc); // Bottom

  // update the list of corners for debug drawing
  m_Corners.clear();
  m_Corners.push_back(na);
  m_Corners.push_back(nb);
  m_Corners.push_back(nd);
  m_Corners.push_back(nb);
  m_Corners.push_back(nd);
  m_Corners.push_back(nc);
  m_Corners.push_back(na);
  m_Corners.push_back(nc);

  m_Corners.push_back(fa);
  m_Corners.push_back(fb);
  m_Corners.push_back(fd);
  m_Corners.push_back(fb);
  m_Corners.push_back(fd);
  m_Corners.push_back(fc);
  m_Corners.push_back(fa);
  m_Corners.push_back(fc);

  m_Corners.push_back(na);
  m_Corners.push_back(fa);
  m_Corners.push_back(nb);
  m_Corners.push_back(fb);
  m_Corners.push_back(nc);
  m_Corners.push_back(fc);
  m_Corners.push_back(nd);
  m_Corners.push_back(fd);
}

bool Frustum::Contains(glm::vec3 p) {
  for (auto plane : m_Planes) {
    if (glm::dot(plane.n, p - plane.d) < 0) {
      return false;
    }
  }
  return true;
}

// this method will treat triangles as intersecting even though they may be
// outside  but it is faster then performing a proper intersection test with
// every plane  and it does not reject triangles that are inside but with all
// corners outside
VolumeTri Frustum::ContainsTriangle(glm::vec3 &a, glm::vec3 &b, glm::vec3 &c) {
  VolumeTri ret = VolumeTri::CONTAINS;
  for (auto plane : m_Planes) {
    char rejects = 0;
    if (glm::dot(plane.n, a - plane.d) < 0) {
      rejects++;
    }
    if (glm::dot(plane.n, b - plane.d) < 0) {
      rejects++;
    }
    if (glm::dot(plane.n, c - plane.d) < 0) {
      rejects++;
    }
    // if all three are outside a plane the triangle is outside the frustrum
    if (rejects >= 3) {
      return VolumeTri::OUTSIDE;
      // if at least one is outside the triangle intersects at least one plane
    }
    if (rejects > 0) {
      ret = VolumeTri::INTERSECT;
    }
  }
  return ret;
}
// same as above but with a volume generated above the triangle
VolumeTri Frustum::ContainsTriVolume(glm::vec3 &a, glm::vec3 &b, glm::vec3 &c,
                                     float height) {
  VolumeTri ret = VolumeTri::CONTAINS;
  for (auto plane : m_Planes) {
    char rejects = 0;
    if (glm::dot(plane.n, a - plane.d) < 0) {
      rejects++;
    }
    if (glm::dot(plane.n, b - plane.d) < 0) {
      rejects++;
    }
    if (glm::dot(plane.n, c - plane.d) < 0) {
      rejects++;
    }
    // if all three are outside a plane the triangle is outside the frustrum
    if (rejects >= 3) {
      if (glm::dot(plane.n, (a * height) - plane.d) < 0) {
        rejects++;
      }
      if (glm::dot(plane.n, (b * height) - plane.d) < 0) {
        rejects++;
      }
      if (glm::dot(plane.n, (c * height) - plane.d) < 0) {
        rejects++;
      }
      if (rejects >= 6) {
        return VolumeTri::OUTSIDE;
      }
      { ret = VolumeTri::INTERSECT; }
    }
    // if at least one is outside the triangle intersects at least one plane
    else if (rejects > 0) {
      ret = VolumeTri::INTERSECT;
    }
  }
  return ret;
}

void Frustum::Draw() {
  glUseProgram(m_pWireShader->GetProgram());
  // Rebind the vertex buffer
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, m_Corners.size() * sizeof(glm::vec3),
               m_Corners.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Pass transformations to the shader
  glUniformMatrix4fv(m_uModelWire, 1, GL_FALSE, glm::value_ptr(m_CullWorld));
  glUniformMatrix4fv(m_uViewProjWire, 1, GL_FALSE,
                     glm::value_ptr(CAMERA->GetViewProj()));

  // Bind Object vertex array
  glBindVertexArray(m_VAO);

  // Draw the object
  glDrawArrays(GL_LINES, 0, m_Corners.size());

  // unbind vertex array
  glBindVertexArray(0);
}

Frustum::~Frustum() {
  glUseProgram(m_pWireShader->GetProgram());
  SafeDelete(m_pWireShader);
}
