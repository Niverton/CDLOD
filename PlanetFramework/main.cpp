#include "ArgvParser.h"
#include "Context.h"      // for Context
#include "InputManager.h" // for InputManager
#include "Scene.h"        // for Scene
#include "Settings.h"     // for Settings, Settings::Window...
#include "glad.h"         // for glGetString, gladLoadGLLoader
#include "utils.h"        // for SafeDelete
#if PLATFORM_Win
#include <IL\il.h>  // for ilInit
#include <IL\ilu.h> // for iluInit
#include <SDL.h>
#include <glm\glm.hpp>
#else
#include <IL/il.h>  // for ilInit
#include <IL/ilu.h> // for iluInit
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#endif
#include <cstdio>   // for fprintf, stderr
#include <cstdlib>  // for atexit, exit, NULL
#include <iostream> // for operator<<, endl, basic_os...
#include <string>   // for char_traits, string

static const char* USAGE =


"\nFor non procedural run on Earth or Moon: just type MOON/EARTH \n\nFor procedurals runs:\n\n"
" <NOISE> --<noise-option>=<value> --<option>\n\n"
"option:\n"
"\t -h  --help      	show this page.\n"
"\t     --fullscreen	start program in fullscreen.\n"
"\t     --use-vsync	start program with vsync.\n"
"\n"
"<NOISE> --<noise-option>=<value>\n"
"Order of options does not matter.\n"
"if you set a flag with a wrong noise, it will be ignored\n\n"
"Common options                     Default value\n"
"\t --width=UInt                    1024\n"
"\t --height=UInt                   1024\n"
"\t --max_height=Float              10.0\n\n"
"SIMPLEX\n"
"\t<common-options>\n\n"
"RIDGEG-NOISE\n"
"\t<common-options>\n\n"
"FLOW-NOISE\n"
"\t<common-options>\n"
"\t--angle=Float                    0.5\n\n"
"FBM\n"
"\t<common-options> \n"
"\t--octave=UInt                    4\n"
"\t--lacunarity=Float               2.0 \n"
"\t--gain=Float                     0.5\n\n"
"WARPED-FBM \n"
"\t<common-options> \n"
"\t--octave=UInt                    4\n"
"\t--lacunarity=Float               2.0\n"
"\t--gain=Float                     0.5\n\n"
"DFBM-WARPED-FBM \n"
"\t--octave=UInt                    4\n"
"\t--lacunarity=Float               2.0\n"
"\t--gain=Float                     0.5\n\n"
"RIDGED-MULTI-FRACTAL \n"
"\t<common-options> \n"
"\t--octave=UInt                    4\n"
"\t--lacunarity=Float               2.0\n"
"\t--gain=Float                     0.5\n";

void usage(const char* msg){
  std::cout << "Usage: "
            << msg
            << USAGE << '\n';
  std::exit(0);
}

//**************************************
// Functions for debugging
//**************************************
static void sdl_die(const char *message) {
  std::cerr << message << ": " << SDL_GetError() << "\n";
  exit(2);
}
#if defined(DEBUG) | defined(_DEBUG)
static void APIENTRY openglCallbackFunction(GLenum source, GLenum type,
                                            GLuint id, GLenum severity,
                                            GLsizei length,
                                            const GLchar *message,
                                            const void *userParam) {
  (void)source;
  (void)type;
  (void)id;
  (void)severity;
  (void)length;
  (void)userParam;
  std::cout << std::endl;
  fprintf(stderr, "%s\n", message);
  if (severity == GL_DEBUG_SEVERITY_HIGH) {
    fprintf(stderr, "Aborting...\n");
    abort();
  }
  std::cout << std::endl;
}
#endif
#ifdef PLATFORM_Win
void SetDebuggingOptions() {
  // notify user if heap is corrupt
  HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

  // Enable run-time memory leak check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  typedef HRESULT(__stdcall * fPtr)(const IID &, void **);

  //_CrtSetBreakAlloc(247);
#endif
}
#endif

//**************************************
// Main
//**************************************
int main(int argc, char **argv) {
  if (argc <= 1) {
    usage(argv[0]);
  }
  
  bool need_h = false;
  bool need_help = false;
  if (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h") {
    usage(argv[0]);
  }
  ArgvParser argvParser{argc, argv};

  argvParser.GetCmdBool("-h", &need_h);
  argvParser.GetCmdBool("--help", &need_help);

  if (need_h || need_help) {
    usage(argv[0]);
  }

  bool use_fullscreen = false;
  argvParser.GetCmdBool("--fullscreen", &use_fullscreen);

  bool use_vsync = false;
  argvParser.GetCmdBool("--use-vsync", &use_vsync);

  // Initialize SDL, OpenGL, DevIL and GLAD
  //**************************************
  //
  // SDL init
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    sdl_die("Couldn't initialize SDL");
  }
  atexit(SDL_Quit);
  SDL_GL_LoadLibrary(nullptr);

  // request opengl context
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

  // Buffers
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

// Request a debug context.
#if defined(DEBUG) | defined(_DEBUG)
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif

  // Create window
  Settings *pSettings = Settings::GetInstance(); // Initialize Game Settings
  pSettings->Window.Fullscreen = use_fullscreen;
  pSettings->Window.VSyncEnabled = use_vsync;

  if (pSettings->Window.Fullscreen) {
    pSettings->Window.pWindow =
        SDL_CreateWindow(pSettings->Window.Title.c_str(),
                         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         pSettings->Window.Width, pSettings->Window.Height,
                         SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP);
  } else {
    pSettings->Window.pWindow = SDL_CreateWindow(
        pSettings->Window.Title.c_str(), SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, pSettings->Window.Width,
        pSettings->Window.Height, SDL_WINDOW_OPENGL);
  }
  if (pSettings->Window.pWindow == nullptr) {
    sdl_die("Couldn't set video mode");
  }

  // OpenGL context creation
  SDL_GLContext context = SDL_GL_CreateContext(pSettings->Window.pWindow);
  if (context == nullptr) {
    sdl_die("Failed to create OpenGL context");
  }
  // Use v-sync
  SDL_GL_SetSwapInterval(static_cast<int>(pSettings->Window.VSyncEnabled));

  // Initialize DevIL

  ilInit();
  iluInit();

  // Bind OpenGL
  std::cout << "OpenGL loaded" << std::endl << std::endl;
  gladLoadGLLoader(SDL_GL_GetProcAddress);
  std::cout << "Vendor: \t" << glGetString(GL_VENDOR) << std::endl;
  std::cout << "Renderer:\t" << glGetString(GL_RENDERER) << std::endl;
  std::cout << "Version:\t" << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLSL Version:\t" << glGetString(GL_SHADING_LANGUAGE_VERSION)
            << std::endl;

// Let OpenGL Log errors
#ifdef _DEBUG
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

  // Disable for OpenGL 3.3 compatibility
  // glDebugMessageCallback(openglCallbackFunction, nullptr);
  // glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL,
  //                      true);
#endif

  // INIT
  //***************

  Context *pContext = Context::GetInstance(); // Initialize scene context
  InputManager *pInput = InputManager::GetInstance(); // init input manager
  pInput->Init();

  // Make a scene :D
  auto *pScene = new Scene(argc, argv, argvParser);
  pScene->Init();

  glEnable(GL_DEPTH_TEST);
  // Main Loop
  while (true) {
    // UPDATE
    //**********

    // user input
    pInput->UpdateEvents();
    if (pInput->IsExitRequested() or
        pInput->IsKeyboardKeyPressed(SDL_SCANCODE_ESCAPE)) {
      break;
    }

    // scene update
    pScene->Update();

    // RENDER
    //******

    // Clear the previous content
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);

    // Let scene draw.
    // custom swapchain with framebuffers will be handled here
    pScene->Draw();
    pScene->PostDraw();

    // Swap front and back buffer
    SDL_GL_SwapWindow(pSettings->Window.pWindow);
  }

  SafeDelete(pScene);

  pInput->DestroyInstance();
  pSettings->DestroyInstance();
  pContext->DestroyInstance();

  SDL_GL_DeleteContext(context);
  SDL_VideoQuit();
  SDL_Quit();
  return 0;
}
