#include "InputManager.h"
#include "utils.h"
#include <cctype>  // for toupper
#include <cstring> // for memcpy, NULL

#if PLATFORM_Win
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

//----------------------------
// Constructor and Destructor
//----------------------------
InputManager::InputManager() {
  m_CharToSdlMap['A'] = SDL_SCANCODE_A;
  m_CharToSdlMap['B'] = SDL_SCANCODE_B;
  m_CharToSdlMap['C'] = SDL_SCANCODE_C;
  m_CharToSdlMap['D'] = SDL_SCANCODE_D;
  m_CharToSdlMap['E'] = SDL_SCANCODE_E;
  m_CharToSdlMap['F'] = SDL_SCANCODE_F;
  m_CharToSdlMap['G'] = SDL_SCANCODE_G;
  m_CharToSdlMap['H'] = SDL_SCANCODE_H;
  m_CharToSdlMap['I'] = SDL_SCANCODE_I;
  m_CharToSdlMap['J'] = SDL_SCANCODE_J;
  m_CharToSdlMap['K'] = SDL_SCANCODE_K;
  m_CharToSdlMap['L'] = SDL_SCANCODE_L;
  m_CharToSdlMap['M'] = SDL_SCANCODE_M;
  m_CharToSdlMap['N'] = SDL_SCANCODE_N;
  m_CharToSdlMap['O'] = SDL_SCANCODE_O;
  m_CharToSdlMap['P'] = SDL_SCANCODE_P;
  m_CharToSdlMap['Q'] = SDL_SCANCODE_Q;
  m_CharToSdlMap['R'] = SDL_SCANCODE_R;
  m_CharToSdlMap['S'] = SDL_SCANCODE_S;
  m_CharToSdlMap['T'] = SDL_SCANCODE_T;
  m_CharToSdlMap['U'] = SDL_SCANCODE_U;
  m_CharToSdlMap['V'] = SDL_SCANCODE_V;
  m_CharToSdlMap['W'] = SDL_SCANCODE_W;
  m_CharToSdlMap['X'] = SDL_SCANCODE_X;
  m_CharToSdlMap['Y'] = SDL_SCANCODE_Y;
  m_CharToSdlMap['Z'] = SDL_SCANCODE_Z;

  m_CharToSdlMap['0'] = SDL_SCANCODE_0;
  m_CharToSdlMap['1'] = SDL_SCANCODE_1;
  m_CharToSdlMap['2'] = SDL_SCANCODE_2;
  m_CharToSdlMap['3'] = SDL_SCANCODE_3;
  m_CharToSdlMap['4'] = SDL_SCANCODE_4;
  m_CharToSdlMap['5'] = SDL_SCANCODE_5;
  m_CharToSdlMap['6'] = SDL_SCANCODE_6;
  m_CharToSdlMap['7'] = SDL_SCANCODE_7;
  m_CharToSdlMap['8'] = SDL_SCANCODE_8;
  m_CharToSdlMap['9'] = SDL_SCANCODE_9;
}
InputManager::~InputManager() {
  delete[] m_pKeyMapNew;
  m_pKeyMapNew = nullptr;
  delete[] m_pKeyMapOld;
  m_pKeyMapOld = nullptr;
  if (!(m_pKeyMapSdl[0] == '\0')) {
    delete m_pKeyMapSdl;
    m_pKeyMapSdl = nullptr;
  }
}
//----------------------------
// MemberFunctions
//----------------------------
void InputManager::Init() {
  m_pKeyMapSdl = SDL_GetKeyboardState(
      &m_KeyboardLength); // Set this map to be constantly updated
  m_pKeyMapNew = new Uint8[m_KeyboardLength];
  m_pKeyMapOld = new Uint8[m_KeyboardLength];
  m_MouseMapNew = SDL_GetMouseState(nullptr, nullptr);
  m_MouseMapOld = m_MouseMapNew;
}
void InputManager::UpdateEvents() {
  std::memcpy(m_pKeyMapOld, m_pKeyMapNew,
              m_KeyboardLength); // Update Old Keyboard state
  m_MouseMapOld = m_MouseMapNew; // Update old Mouse state
  // Pump SDL events
  SDL_Event evnt{};
  while (SDL_PollEvent(&evnt) != 0) {
    switch (evnt.type) {
    case SDL_QUIT:
      m_ExitRequested = true;
      break;
    case SDL_WINDOWEVENT:
      switch (evnt.window.event) {
      case SDL_WINDOWEVENT_CLOSE:
        m_ExitRequested = true;
        break;
      }
      break;
    }
  }
  std::memcpy(m_pKeyMapNew, m_pKeyMapSdl,
              m_KeyboardLength); // Update New Keyboard state
  int mPosOldX = m_MousePosX;
  int mPosOldY = m_MousePosY;
  m_MouseMapNew = SDL_GetMouseState(
      &m_MousePosX, &m_MousePosY); // Update new Mouse state and position
  m_MouseMove = glm::vec2(static_cast<float>(m_MousePosX - mPosOldX),
                          static_cast<float>(m_MousePosY - mPosOldY));
}
//----------------------------
// Getters
//----------------------------
bool InputManager::IsExitRequested() {
  return m_ExitRequested;
}
//----------------------------
// Keyboard
//----------------------------
bool InputManager::GetScancode(SDL_Scancode &code, char key) {
  key = static_cast<char>(toupper(key));
  if (m_CharToSdlMap.find(key) == m_CharToSdlMap.end()) {
    return false;
  }
  code = m_CharToSdlMap[key];
  return true;
}
bool InputManager::IsKeyboardKeyPressed(SDL_Scancode key) {
  return (m_pKeyMapNew[key] != 0u) && (m_pKeyMapOld[key] == 0u);
}
bool InputManager::IsKeyboardKeyPressed(char key) {
  SDL_Scancode sKey;
  if (GetScancode(sKey, key)) {
    return (m_pKeyMapNew[sKey] != 0u) && (m_pKeyMapOld[sKey] == 0u);
  }
  return false;
}
bool InputManager::IsKeyboardKeyDown(SDL_Scancode key) {
  return (m_pKeyMapNew[key] != 0u) && (m_pKeyMapOld[key] != 0u);
}
bool InputManager::IsKeyboardKeyDown(char key) {
  SDL_Scancode sKey;
  if (GetScancode(sKey, key)) {
    return (m_pKeyMapNew[sKey] != 0u) && (m_pKeyMapOld[sKey] != 0u);
  }
  return false;
}
bool InputManager::IsKeyboardKeyReleased(SDL_Scancode key) {
  return (m_pKeyMapNew[key] == 0u) && (m_pKeyMapOld[key] != 0u);
}
bool InputManager::IsKeyboardKeyReleased(char key) {
  SDL_Scancode sKey;
  if (GetScancode(sKey, key)) {
    return (m_pKeyMapNew[sKey] == 0u) && (m_pKeyMapOld[sKey] != 0u);
  }
  return false;
}
//----------------------------
// Mouse
//----------------------------
bool InputManager::IsMouseButtonPressed(int button) {
  return ((m_MouseMapNew & SDL_BUTTON(button)) != 0u) &&
         ((m_MouseMapOld & SDL_BUTTON(button)) == 0u);
}
bool InputManager::IsMouseButtonDown(int button) {
  return ((m_MouseMapNew & SDL_BUTTON(button)) != 0u) &&
         ((m_MouseMapOld & SDL_BUTTON(button)) != 0u);
}
bool InputManager::IsMouseButtonReleased(int button) {
  return ((m_MouseMapNew & SDL_BUTTON(button)) == 0u) &&
         ((m_MouseMapOld & SDL_BUTTON(button)) != 0u);
}
glm::vec2 InputManager::GetMousePosition() {
  return glm::vec2(static_cast<float>(m_MousePosX),
                   static_cast<float>(m_MousePosY));
}
