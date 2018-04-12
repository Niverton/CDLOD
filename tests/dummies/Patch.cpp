#include "Patch.h"
#include <vector>

Patch::Patch(short levels) : m_Levels(levels) {
}

void Patch::Init() {
}

void Patch::GenerateGeometry(short levels) {
}

void Patch::BindInstances(std::vector<PatchInstance> &instances) {
}

void Patch::UploadDistanceLUT(std::vector<float> &distances) {
}

void Patch::Draw(bool white) {
}

Patch::~Patch() {
}
