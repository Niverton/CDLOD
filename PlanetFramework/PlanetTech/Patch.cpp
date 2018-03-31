#include "Patch.h"
#include "Camera.h" // for Camera
#include "Context.h"
#include "Frustum.h"      // for Frustum
#include "Planet.h"       // for Planet
#include "Shader.h"       // for Shader
#include "Texture.h"      // for Texture
#include "Transform.h"    // for Transform
#include "Triangulator.h" // for Triangulator
#include <cmath>          // for pow
#include <cstddef>        // for offsetof, size_t
#include <string>         // for allocator, operator+, to_string

#if PLATFORM_Win
#include <SDL.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#else
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#endif

Patch::Patch(short levels) : m_Levels(levels) {
  m_pPatchShader = new Shader("./Shaders/patch.glsl");
}

void Patch::Init() {
  // Shader Init
  //***********
  m_pPatchShader->Build();
  glUseProgram(m_pPatchShader->GetProgram());
  m_uCamPos = glGetUniformLocation(m_pPatchShader->GetProgram(), "camPos");
  m_uRadius = glGetUniformLocation(m_pPatchShader->GetProgram(), "radius");
  m_uMorphRange =
      glGetUniformLocation(m_pPatchShader->GetProgram(), "morphRange");

  m_uMaxHeight =
      glGetUniformLocation(m_pPatchShader->GetProgram(), "maxHeight");

  m_uModel = glGetUniformLocation(m_pPatchShader->GetProgram(), "model");
  m_uViewProj = glGetUniformLocation(m_pPatchShader->GetProgram(), "viewProj");

  m_uAmbient = glGetUniformLocation(m_pPatchShader->GetProgram(), "ambient");

  glUniform1i(glGetUniformLocation(m_pPatchShader->GetProgram(), "texDiffuse"),
              0);
  glUniform1i(glGetUniformLocation(m_pPatchShader->GetProgram(), "texHeight"),
              1);

  // Buffer Initialisation
  //*********************
  // Generate buffers and arrays
  glGenVertexArrays(1, &m_VAO);
  glGenBuffers(1, &m_VBO);
  glGenBuffers(1, &m_EBO);
  glGenBuffers(1, &m_VBOInstance);
  // bind
  glBindVertexArray(m_VAO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  // input layout
  //************
  // geometry
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(PatchVertex),
                        (GLvoid *)offsetof(PatchVertex, pos));
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(PatchVertex),
                        (GLvoid *)offsetof(PatchVertex, morph));
  // instances
  // bind
  glBindBuffer(GL_ARRAY_BUFFER, m_VBOInstance);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);
  glEnableVertexAttribArray(4);
  glEnableVertexAttribArray(5);
  glVertexAttribIPointer(2, 1, GL_INT, sizeof(PatchInstance),
                         (GLvoid *)offsetof(PatchInstance, level));
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(PatchInstance),
                        (GLvoid *)offsetof(PatchInstance, a));
  glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(PatchInstance),
                        (GLvoid *)offsetof(PatchInstance, r));
  glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(PatchInstance),
                        (GLvoid *)offsetof(PatchInstance, s));
  glVertexAttribDivisor(2, 1);
  glVertexAttribDivisor(3, 1);
  glVertexAttribDivisor(4, 1);
  glVertexAttribDivisor(5, 1);
  // Indices
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  // unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  GenerateGeometry(m_Levels);
}

void Patch::GenerateGeometry(short levels) {
  // clear
  m_Vertices.clear();
  m_Indices.clear();
  // Generate
  m_Levels = levels;
  m_RC = 1 + static_cast<unsigned int>(pow(2, static_cast<int>(m_Levels)));

  float delta = 1 / static_cast<float>(m_RC - 1);

  UINT rowIdx = 0;
  UINT nextIdx = 0;
  for (UINT row = 0; row < m_RC; row++) {
    UINT numCols = m_RC - row;
    nextIdx += numCols;
    for (UINT column = 0; column < numCols; column++) {
      // calc position
      glm::vec2 pos = glm::vec2(column / static_cast<float>(m_RC - 1),
                                row / static_cast<float>(m_RC - 1));
      // calc morph
      glm::vec2 morph = glm::vec2(0, 0);
      if (row % 2 == 0) {
        if (column % 2 == 1) {
          morph = glm::vec2(-delta, 0);
        }
      } else {
        if (column % 2 == 0) {
          morph = glm::vec2(0, delta);
        } else {
          morph = glm::vec2(delta, -delta);
        }
      }
      // create vertex
      m_Vertices.emplace_back(pos, morph);
      // calc index
      if (row < m_RC - 1 && column < numCols - 1) {
        m_Indices.push_back(rowIdx + column);
        m_Indices.push_back(nextIdx + column);
        m_Indices.push_back(1 + rowIdx + column);
        if (column < numCols - 2) {
          m_Indices.push_back(nextIdx + column);
          m_Indices.push_back(1 + nextIdx + column);
          m_Indices.push_back(1 + rowIdx + column);
        }
      }
    }
    rowIdx = nextIdx;
  }
  // Rebind dat shizzle
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(PatchVertex),
               m_Vertices.data(), GL_DYNAMIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_Indices.size(),
               m_Indices.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Patch::BindInstances(std::vector<PatchInstance> &instances) {
  // update buffer
  m_NumInstances = instances.size();
  glBindBuffer(GL_ARRAY_BUFFER, m_VBOInstance);
  glBufferData(GL_ARRAY_BUFFER, instances.size() * sizeof(PatchInstance),
               instances.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Patch::UploadDistanceLUT(std::vector<float> &distances) {
  glUseProgram(m_pPatchShader->GetProgram());
  for (size_t i = 0; i < distances.size(); i++) {
    glUniform1f(glGetUniformLocation(
                    m_pPatchShader->GetProgram(),
                    ("distanceLUT[" + std::to_string(i) + "]").c_str()),
                distances[i]);
  }
}

void Patch::Draw(bool white) {
  // Enable this objects shader
  glUseProgram(m_pPatchShader->GetProgram());

  // Pass transformations to the shader
  glUniformMatrix4fv(m_uModel, 1, GL_FALSE,
                     glm::value_ptr(m_pPlanet->GetTransform()->GetTransform()));
  glUniformMatrix4fv(m_uViewProj, 1, GL_FALSE,
                     glm::value_ptr(CAMERA->GetViewProj()));

  // Set other uniforms here too!
  glm::vec3 camPos =
      m_pPlanet->GetTriangulator()->GetFrustum()->GetPositionOS();
  glUniform3f(m_uCamPos, camPos.x, camPos.y, camPos.z);
  glUniform1f(m_uRadius, m_pPlanet->GetRadius());
  glUniform1f(m_uMorphRange, m_MorphRange);

  glm::vec3 amb = white ? glm::vec3(10, 10, 10) : m_Ambient;
  glUniform3f(m_uAmbient, amb.x, amb.y, amb.z);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_pPlanet->GetDiffuseMap()->GetHandle());
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, m_pPlanet->GetHeightMap()->GetHandle());

  // Bind Object vertex array
  glBindVertexArray(m_VAO);

  // Draw the object
  glDrawElementsInstanced(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT,
                          nullptr, m_NumInstances);

  // unbind vertex array
  glBindVertexArray(0);
}

Patch::~Patch() {
  glUseProgram(m_pPatchShader->GetProgram());
  SafeDelete(m_pPatchShader);

  glDeleteVertexArrays(1, &m_EBO);
  glDeleteVertexArrays(1, &m_VAO);
  glDeleteBuffers(1, &m_VBO);
}
