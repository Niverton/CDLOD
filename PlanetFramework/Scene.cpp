
#include "Scene.h"
#include "stdafx.h"

#include "./PlanetTech/Types/Earth.h"
#include "./PlanetTech/Types/Moon.h"
#include "./PlanetTech/Types/Procedural.h"
#include "Camera.h"
#include "SpriteFont.h"
#include "TextRenderer.h"

#include <iomanip>
#include <sstream>
#include <string>
#include <cstdlib>

//#include "Screenshot.h"

Scene::Scene(int argc, char** argv, ArgvParser& parser) {
  CreatePlanetFromArgs(argc, argv, parser);

  //m_pPlanet = new Moon();
  m_pDebugFont = new SpriteFont();
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
  if (INPUT->IsKeyboardKeyPressed(SDL_SCANCODE_F2))
    m_DrawUI = !m_DrawUI;
  if (INPUT->IsKeyboardKeyPressed(SDL_SCANCODE_F1)) {
    //	Screenshot::GetInstance()->Take();
  }

  m_pPlanet->Update();
}

void Scene::Draw() {
  // Draw debug info
  TextRenderer::GetInstance()->SetFont(m_pDebugFont);
  TextRenderer::GetInstance()->SetColor(glm::vec4(1, 0.3f, 0.3f, 1));
  auto fpsStr = std::string("FPS: ") + std::to_string((int)TIME->FPS());
  TextRenderer::GetInstance()->DrawText(fpsStr, glm::vec2(20, 20));

  TextRenderer::GetInstance()->SetColor(glm::vec4(1, 1, 1, 1));
  auto vertStr = std::string("vertex count: ") +
                 std::to_string(m_pPlanet->GetVertexCount());
  TextRenderer::GetInstance()->DrawText(vertStr, glm::vec2(20, 60));

  std::stringstream ss;
  ss << std::fixed << std::setprecision(3) << m_pCamera->GetAltitude();
  auto altStr = std::string("altitude: ") + ss.str() + "km";
  TextRenderer::GetInstance()->DrawText(altStr, glm::vec2(20, 100));

  auto fovStr = std::string("FOV: ") + std::to_string(m_pCamera->GetFOV());
  TextRenderer::GetInstance()->DrawText(fovStr, glm::vec2(20, 140));

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
  if (m_DrawUI)
    TextRenderer::GetInstance()->Draw();
}

void Scene::PostDraw() {
  // Take a screenshot
  // Screenshot::GetInstance()->Capture();
}

Scene::~Scene() {
  SafeDelete(m_pPlanet);

  SafeDelete(m_pDebugFont);
  TextRenderer::GetInstance()->DestroyInstance();
  // Screenshot::GetInstance()->DestroyInstance();

  SafeDelete(m_pTime);
  SafeDelete(m_pCamera);
  SafeDelete(m_pConObj);
}

void Scene::CreatePlanetFromArgs(int argc, char** argv, ArgvParser& argvParser){
  if (argc == 1) {
    //Create default planet
    ProceduralPlanet::Properties prop;
    m_pPlanet = new ProceduralPlanet(&prop);
  } else {
    std::string noise = argvParser.GetMode();
    std::cout << '\n';

    if (noise == "SIMPLEX" || noise == "simplex") {
      ProceduralPlanet::Properties prop;
      prop.noise = ProceduralPlanet::Noise::SIMPLEX;
      argvParser.GetCmdInt<unsigned int>("--width", &prop.width);
      argvParser.GetCmdInt<unsigned int>("--height", &prop.height);
      argvParser.GetCmdFloat<float>("--max-height", &prop.maxHeight);
      argvParser.GetCmdFloat<float>("--radius", &prop.radius);

      check_value<float>(prop.radius, 0, 1737.1);
      check_value<unsigned int>(prop.width, 0, 800);
      check_value<unsigned int>(prop.height, 0, 800);
      check_value<float>(prop.maxHeight, 0, 10.0);

      std::cout << "SIMPLEX:\n";
      std::cout << "Width: " << prop.width << '\n';
      std::cout << "Height: " << prop.height<< '\n';
      std::cout << "MaxHeight: " << prop.maxHeight << '\n';

      m_pPlanet = new ProceduralPlanet(&prop);
    } else if (noise == "PERLIN" || noise == "perlin") {
      ProceduralPlanet::Properties prop;
      prop.noise = ProceduralPlanet::Noise::PERLIN;

      argvParser.GetCmdInt<unsigned int>("--width", &prop.width);
      argvParser.GetCmdInt<unsigned int>("--height", &prop.height);
      argvParser.GetCmdFloat<float>("--max-height", &prop.maxHeight);
      argvParser.GetCmdFloat<float>("--radius", &prop.radius);

      check_value<float>(prop.radius, 0, 1737.1);
      check_value<unsigned int>(prop.width, 0, 800);
      check_value<unsigned int>(prop.height, 0, 800);
      check_value<float>(prop.maxHeight, 0, 10.0);

      std::cout << "PERLIN\n";
      std::cout << "Width: " << prop.width << '\n';
      std::cout << "Height: " << prop.height<< '\n';
      std::cout << "MaxHeight: " << prop.maxHeight << '\n';
      m_pPlanet = new ProceduralPlanet(&prop);
    } else if (noise == "RIDGED-NOISE" || noise == "ridged-noise") {
      ProceduralPlanet::Properties prop;
      prop.noise = ProceduralPlanet::Noise::RIDGED_NOISE;

      argvParser.GetCmdInt<unsigned int>("--width", &prop.width);
      argvParser.GetCmdInt<unsigned int>("--height", &prop.height);
      argvParser.GetCmdFloat<float>("--max-height", &prop.maxHeight);
      argvParser.GetCmdFloat<float>("--radius", &prop.radius);

      check_value<float>(prop.radius, 0, 1737.1);
      check_value<unsigned int>(prop.width, 0, 800);
      check_value<unsigned int>(prop.height, 0, 800);
      check_value<float>(prop.maxHeight, 0, 10.0);

      std::cout << "RIDGED NOISE\n";
      std::cout << "Width: " << prop.width << '\n';
      std::cout << "Height: " << prop.height<< '\n';
      std::cout << "MaxHeight: " << prop.maxHeight << '\n';
      
      m_pPlanet = new ProceduralPlanet(&prop);
    } else if (noise == "FLOW-NOISE" || noise == "flow-noise"){
      FlowNoiseProperties prop;
    
      prop.noise = ProceduralPlanet::Noise::FLOW_NOISE;
      argvParser.GetCmdInt<unsigned int>("--width", &prop.width);
      argvParser.GetCmdInt<unsigned int>("--height", &prop.height);
      argvParser.GetCmdFloat<float>("--max-height", &prop.maxHeight);
      argvParser.GetCmdFloat<float>("--angle", &prop.angle);
      argvParser.GetCmdFloat<float>("--radius", &prop.radius);

      check_value<float>(prop.radius, 0, 1737.1);
      check_value<unsigned int>(prop.width, 0, 800);
      check_value<unsigned int>(prop.height, 0, 800);
      check_value<float>(prop.maxHeight, 0, 10.0);
      check_value<float>(prop.angle, 0, 0.5);

      std::cout << "FLOW NOISE\n";
      std::cout << "Width: " << prop.width << '\n';
      std::cout << "Height: " << prop.height<< '\n';
      std::cout << "MaxHeight: " << prop.maxHeight << '\n';
      std::cout << "Angle: " << prop.angle << '\n';

      m_pPlanet = new ProceduralPlanet(static_cast<ProceduralPlanet::Properties*>
                                        (&prop));
    } else if ( noise == "FBM" || noise == "fbm") {
      FbmProperties prop;
    
      prop.noise = ProceduralPlanet::Noise::FBM;
      argvParser.GetCmdInt<unsigned int>("--width", &prop.width);
      argvParser.GetCmdInt<unsigned int>("--height", &prop.height);
      argvParser.GetCmdFloat<float>("--max-height", &prop.maxHeight);
      argvParser.GetCmdInt<unsigned int>("--octave", &prop.octave);
      argvParser.GetCmdFloat<float>("--lacunarity", &prop.lacunarity);
      argvParser.GetCmdFloat<float>("--gain", &prop.gain);
      argvParser.GetCmdFloat<float>("--radius", &prop.radius);

      check_value<float>(prop.radius, 0, 1737.1);
      check_value<unsigned int>(prop.width, 0, 800);
      check_value<unsigned int>(prop.height, 0, 800);
      check_value<unsigned int>(prop.octave, 0, 4);
      check_value<float>(prop.maxHeight, 0, 10.0);
      check_value<float>(prop.lacunarity, 0, 2.0);
      check_value<float>(prop.gain, 0, 0.5);

      std::cout << "FBM\n";
      std::cout << "Width: " << prop.width << '\n';
      std::cout << "Height: " << prop.height<< '\n';
      std::cout << "MaxHeight: " << prop.maxHeight << '\n';
      std::cout << "Octave: " << prop.octave << '\n';
      std::cout << "Lacuranity: " << prop.lacunarity << '\n';
      std::cout << "Gain: " << prop.gain << '\n';
     
      m_pPlanet = new ProceduralPlanet(static_cast<ProceduralPlanet::Properties*>
                                        (&prop));
    } else if (noise == "WARPED-FBM" || noise == "warped-fbm") {
      FbmProperties prop;
    
      prop.noise = ProceduralPlanet::Noise::WARPED_FBM;
      argvParser.GetCmdInt<unsigned int>("--width", &prop.width);
      argvParser.GetCmdInt<unsigned int>("--height", &prop.height);
      argvParser.GetCmdFloat<float>("--max-height", &prop.maxHeight);
      argvParser.GetCmdInt<unsigned int>("--octave", &prop.octave);
      argvParser.GetCmdFloat<float>("--lacunarity", &prop.lacunarity);
      argvParser.GetCmdFloat<float>("--gain", &prop.gain);
      argvParser.GetCmdFloat<float>("--radius", &prop.radius);

      check_value<float>(prop.radius, 0, 1737.1);
      check_value<unsigned int>(prop.width, 0, 800);
      check_value<unsigned int>(prop.height, 0, 800);
      check_value<unsigned int>(prop.octave, 0, 4);
      check_value<float>(prop.maxHeight, 0, 10.0);
      check_value<float>(prop.lacunarity, 0, 2.0);
      check_value<float>(prop.gain, 0, 0.5);

      std::cout << "FBM WARPPED\n";
      std::cout << "Width: " << prop.width << '\n';
      std::cout << "Height: " << prop.height<< '\n';
      std::cout << "MaxHeight: " << prop.maxHeight << '\n';
      std::cout << "Octave: " << prop.octave << '\n';
      std::cout << "Lacuranity: " << prop.lacunarity << '\n';
      std::cout << "Gain: " << prop.gain << '\n';
     
      m_pPlanet = new ProceduralPlanet(static_cast<ProceduralPlanet::Properties*>
                                        (&prop));
    } else if (noise == "DFBM-WARPED-FBM" || noise == "dfbm-warper-fbm") {
      FbmProperties prop;
    
      prop.noise = ProceduralPlanet::Noise::DFBM_WARPED_FBM;
      argvParser.GetCmdInt<unsigned int>("--width", &prop.width);
      argvParser.GetCmdInt<unsigned int>("--height", &prop.height);
      argvParser.GetCmdFloat<float>("--max-height", &prop.maxHeight);
      argvParser.GetCmdInt<unsigned int>("--octave", &prop.octave);
      argvParser.GetCmdFloat<float>("--lacunarity", &prop.lacunarity);
      argvParser.GetCmdFloat<float>("--gain", &prop.gain);
      argvParser.GetCmdFloat<float>("--radius", &prop.radius);

      check_value<float>(prop.radius, 0, 1737.1);
      check_value<unsigned int>(prop.width, 0, 800);
      check_value<unsigned int>(prop.height, 0, 800);
      check_value<unsigned int>(prop.octave, 0, 4);
      check_value<float>(prop.maxHeight, 0, 10.0);
      check_value<float>(prop.lacunarity, 0, 2.0);
      check_value<float>(prop.gain, 0, 0.5);

      std::cout << "DFBM WARPED FBM\n";
      std::cout << "Width: " << prop.width << '\n';
      std::cout << "Height: " << prop.height<< '\n';
      std::cout << "MaxHeight: " << prop.maxHeight << '\n';
      std::cout << "Octave: " << prop.octave << '\n';
      std::cout << "Lacuranity: " << prop.lacunarity << '\n';
      std::cout << "Gain: " << prop.gain << '\n';
     
      m_pPlanet = new ProceduralPlanet(static_cast<ProceduralPlanet::Properties*>
                                        (&prop));
    } else if (noise == "RIDGED-MULTI-FRACTAL" || noise == "ridged-multi-fractal") {
      RidgedMultiFractalVariationProperties prop;
    
      prop.noise = ProceduralPlanet::Noise::RIDGED_MULTI_FRACTAL_VARIATION;
      argvParser.GetCmdInt<unsigned int>("--width", &prop.width);
      argvParser.GetCmdInt<unsigned int>("--height", &prop.height);
      argvParser.GetCmdFloat<float>("--max-height", &prop.maxHeight);
      argvParser.GetCmdInt<unsigned int>("--octave", &prop.octave);
      argvParser.GetCmdFloat<float>("--lacunarity", &prop.lacunarity);
      argvParser.GetCmdFloat<float>("--gain", &prop.gain);
      argvParser.GetCmdFloat<float>("--offset", &prop.ridgeOffset);
      argvParser.GetCmdFloat<float>("--radius", &prop.radius);

      check_value<float>(prop.radius, 0, 1737.1);
      check_value<unsigned int>(prop.width, 0, 800);
      check_value<unsigned int>(prop.height, 0, 800);
      check_value<unsigned int>(prop.octave, 0, 4);
      check_value<float>(prop.maxHeight, 0, 10.0);
      check_value<float>(prop.lacunarity, 0, 2.0);
      check_value<float>(prop.gain, 0, 0.5);
      check_value<float>(prop.ridgeOffset, 0, 0.1);

      std::cout << "RIDGED MULTI FRACTAL VARIATION\n";
      std::cout << "Width: " << prop.width << '\n';
      std::cout << "Height: " << prop.height<< '\n';
      std::cout << "MaxHeight: " << prop.maxHeight << '\n';
      std::cout << "Octave: " << prop.octave << '\n';
      std::cout << "Lacuranity: " << prop.lacunarity << '\n';
      std::cout << "Gain: " << prop.gain << '\n';
     
      m_pPlanet = new ProceduralPlanet(static_cast<ProceduralPlanet::Properties*>
                                        (&prop));
    } else {
      std::cerr << "Error: " << argv[1] << " is incorrect noise.\n";
      std::cerr << argv[0] << " start with default options.\n";
      ProceduralPlanet::Properties prop;

      std::cerr << "Default options: \n"
                << "  Noise: SIMPLEX\n"
                << "  Width: " << prop.width << '\n'
                << "  Height: " << prop.height << '\n'
                << "  MaxHeight: " << prop.maxHeight << '\n';
 
      m_pPlanet = new ProceduralPlanet(&prop);
    }
  }
}
