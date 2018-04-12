#include "Frustum.h"

Frustum::Frustum() {
}

void Frustum::Init() {
}

// create transforms to prevent transforming every triangle into world space
void Frustum::SetCullTransform(glm::mat4 objectWorld) {
}

void Frustum::SetToCamera(Camera *pCamera) {
}

void Frustum::Update() {
}

bool Frustum::Contains(glm::vec3 p) {
  return false;
}

VolumeTri Frustum::ContainsTriangle(glm::vec3 &a, glm::vec3 &b, glm::vec3 &c) {
  return VolumeTri::CONTAINS;
}
// same as above but with a volume generated above the triangle
VolumeTri Frustum::ContainsTriVolume(glm::vec3 &a, glm::vec3 &b, glm::vec3 &c,
                                     float height) {
  return VolumeTri::CONTAINS;
}

void Frustum::Draw() {
}

Frustum::~Frustum() {
}
