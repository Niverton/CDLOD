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
