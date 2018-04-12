#include "Scene.h"
#include "Camera.h"           // for Camera
#include "Context.h"          // for ContextObjects, Context
#include "InputManager.h"     // for InputManager
#include "Planet.h"           // for Planet
#include "SpriteFont.h"       // for SpriteFont
#include "TextRenderer.h"     // for TextRenderer
#include "Time.h"             // for Time
#include "Types/Earth.h"      // for Earth
#include "Types/Moon.h"       // for Moon
#include "Types/Procedural.h" // for ProceduralPlanet
#include "glad.h"             // for GL_FRONT_AND_BACK, glDepth...
#include "utils.h"            // for SafeDelete, INPUT, CONTEXT
#include <array>
#include <cstdlib> // for std::exit, EXIT_FAILURE
#include <iomanip> // for operator<<, setprecision
#include <sstream> // for stringstream, basic_ostream
#include <string>  // for operator+, allocator, to_s...

#define PLANET_ERROR                                                           \
  "Error: could not create planet, you must have set an invalid value"

//#include "Screenshot.h"

Scene::Scene(int argc, ArgvParser &parser) : m_pDebugFont{new SpriteFont()} {
  CreatePlanetFromArgs(argc, parser);
}

void Scene::Init() {
  // Set scene context
  m_pTime = new Time();
  m_pCamera = new Camera();
  m_pConObj = new ContextObjects();
  m_pConObj->pTime = m_pTime;
  m_pConObj->pCamera = m_pCamera;
  m_pConObj->pScene = this;
  CONTEXT->SetContext(m_pConObj);

  // Initialize text rendering
  TextRenderer::GetInstance()->Init();
  m_pDebugFont->Load("./Fonts/Consolas_32.fnt");

  // Init screenshot capturer
  // Screenshot::GetInstance()->Init("./Screenshots/");

  // Init planet stuff
  m_pPlanet->Init();
  m_pCamera->SetPlanet(m_pPlanet);

  // start time
  m_pConObj->pTime->Start();
}

void Scene::Update() {
  m_pConObj->pTime->Update();
  m_pCamera->Update();

  if (INPUT->IsKeyboardKeyPressed('z')) {
    switch (renderMode) {
    case Scene::SOLID:
      renderMode = WIREFRAME;
      break;
    case Scene::WIREFRAME:
      renderMode = OVERLAY;
      break;
    case Scene::OVERLAY:
      renderMode = SOLID;
      break;
    }
  }
  if (INPUT->IsKeyboardKeyPressed(SDL_SCANCODE_F2)) {
    m_DrawUI = !m_DrawUI;
  }
  if (INPUT->IsKeyboardKeyPressed(SDL_SCANCODE_F1)) {
    //	Screenshot::GetInstance()->Take();
  }

  m_pPlanet->Update();
}

void Scene::Draw() {
  using sstr = std::stringstream;
  auto *TR = TextRenderer::GetInstance();
  // Draw debug info
  TR->SetFont(m_pDebugFont);
  TR->SetColor(glm::vec4(1, 0.3f, 0.3f, 1));
  sstr fpsStr;
  fpsStr << "FPS: " << std::setw(4) << static_cast<int>(TIME->FPS()) << " ("
         << std::setw(4) << std::ceil(TIME->DeltaTime() * 1000) << "ms)";
  TR->DrawText(fpsStr.str(), glm::vec2(20, 20));

  TR->SetColor(glm::vec4(1, 1, 1, 1));
  sstr vertStr;
  vertStr << "Vertex count: " << std::setw(4) << m_pPlanet->GetVertexCount();
  TR->DrawText(vertStr.str(), glm::vec2(20, 60));

  sstr altStr;
  altStr << "Altitude: " << std::fixed << std::setprecision(3)
         << m_pCamera->GetAltitude() << "km";
  TR->DrawText(altStr.str(), glm::vec2(20, 100));

  sstr fovStr;
  fovStr << "FOV: " << m_pCamera->GetFOV();
  TR->DrawText(fovStr.str(), glm::vec2(20, 140));

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glDepthRange(0.00001, 1.0);
  if (renderMode == SOLID || renderMode == OVERLAY) {
    m_pPlanet->Draw();
  }

  // Debug Drawing
  glDepthRange(0.0, 0.999999);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  if (renderMode == WIREFRAME || renderMode == OVERLAY) {
    // m_pPlanet->Draw();
    m_pPlanet->DrawWire();
  }

  // Draw text
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glDepthRange(0.000001, 1.0);
  if (m_DrawUI) {
    TR->Draw();
  }
}

void Scene::PostDraw() {
  // Take a screenshot
  // Screenshot::GetInstance()->Capture();
}

Scene::~Scene() {
  SafeDelete(m_pPlanet);

  SafeDelete(m_pDebugFont);
  TextRenderer::DestroyInstance();
  // Screenshot::GetInstance()->DestroyInstance();

  SafeDelete(m_pTime);
  SafeDelete(m_pCamera);
  SafeDelete(m_pConObj);
}

void Scene::CreatePlanetFromArgs(int argc, ArgvParser &argvParser) {
  if (argc == 1) {
    // Create default planet
    ProceduralPlanet::Properties prop;
    m_pPlanet = new ProceduralPlanet(&prop);
  } else {
    ProceduralPlanet::Properties prop;

    const std::array<std::string, 8> NOISES = {
        "SIMPLEX", "PERLIN",     "RIDGED-NOISE",    "FLOW-NOISE",
        "FBM",     "WARPED-FBM", "DFBM-WARPED-FBM", "RIDGED-MULTI-FRACTAL"};

    const std::array<std::string, 8> noises = {
        "simplex", "perlin",     "ridged-noise",    "flow-noise",
        "fbm",     "warped-fbm", "dfbm-warped-fbm", "ridged-multi-fractal"};

    std::string noise = argvParser.GetMode();
    if (noise == "MOON" || noise == "moon") {
      m_pPlanet = new Moon();
    } else if (noise == "EARTH" || noise == "earth") {
      m_pPlanet = new Earth();
    } else {

      argvParser.GetCmdInt<unsigned int>("--width", &prop.width);
      argvParser.GetCmdInt<unsigned int>("--height", &prop.height);
      argvParser.GetCmdFloat("--max-height", &prop.maxHeight);
      argvParser.GetCmdInt<unsigned int>("--octave", &prop.octave);
      argvParser.GetCmdFloat("--lacunarity", &prop.lacunarity);
      argvParser.GetCmdFloat("--gain", &prop.gain);
      argvParser.GetCmdFloat("--offset", &prop.ridgeOffset);
      argvParser.GetCmdFloat("--radius", &prop.radius);

      check_value<float>(prop.radius, 0, 1737.1);
      check_value<unsigned int>(prop.width, 0, 1024);
      check_value<unsigned int>(prop.height, 0, 1024);
      check_value<unsigned int>(prop.octave, 0, 4);
      check_value<float>(prop.maxHeight, 0, 10.0);
      check_value<float>(prop.lacunarity, 0, 2.0);
      check_value<float>(prop.gain, 0, 0.5);
      check_value<float>(prop.ridgeOffset, 0, 0.1);

      bool found = false;
      for (int i = 0; i < 8; i++) {
        if (noise == NOISES[i] || noise == noises[i]) {
          found = true;
          prop.noise = static_cast<ProceduralPlanet::Noise>(i);
        }
      }
      if (!found) {
        std::cerr << "Error please specify a correct noise, see usage for more "
                     "info.\n";
        std::exit(EXIT_FAILURE);
      }

      try {
        m_pPlanet = new ProceduralPlanet(&prop);
      } catch (...) {
        std::cerr << PLANET_ERROR << '\n';
        std::exit(EXIT_FAILURE);
      }
    }
  }
}
