cmake_minimum_required(VERSION 3.7.2)

#Export build configuration for external tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(PlanetRenderer)

set(GLM_USE_NATIVE NO CACHE BOOL
  "Pretend CMake found GLM and use native lib ?")
set(DOXYGEN_ONLY_PUBLIC NO CACHE BOOL
  "Generate only public documentation")
set(KEEP_DOT NO CACHE BOOL
  "Should doxygen keep the .dot files ?")
set(NO_SVG NO CACHE BOOL
  "Disable SVG output")
set(ASAN NO CACHE BOOL
  "Enable -fsanitize=address ?")
set(SANAL NO CACHE BOOL
  "Run static analysers during build ?")


# Fichiers source
set(SRCS
  PlanetFramework/BinaryReader.cpp
  PlanetFramework/BinaryReader.h
  PlanetFramework/Camera.cpp
  PlanetFramework/Camera.h
  PlanetFramework/Context.h
  PlanetFramework/InputManager.cpp
  PlanetFramework/InputManager.h
  PlanetFramework/main.cpp
  PlanetFramework/PlanetTech/Frustum.cpp
  PlanetFramework/PlanetTech/Frustum.h
  PlanetFramework/PlanetTech/Patch.cpp
  PlanetFramework/PlanetTech/Patch.h
  PlanetFramework/PlanetTech/Planet.cpp
  PlanetFramework/PlanetTech/Planet.h
  PlanetFramework/PlanetTech/stdafx.h
  PlanetFramework/PlanetTech/Triangulator.cpp
  PlanetFramework/PlanetTech/Triangulator.h
  PlanetFramework/PlanetTech/Types/Earth.cpp
  PlanetFramework/PlanetTech/Types/Earth.h
  PlanetFramework/PlanetTech/Types/Moon.cpp
  PlanetFramework/PlanetTech/Types/Moon.h
  PlanetFramework/PlanetTech/Types/stdafx.h
  PlanetFramework/Scene.cpp
  PlanetFramework/Scene.h
  PlanetFramework/Screenshot.cpp
  PlanetFramework/Screenshot.h
  PlanetFramework/Settings.h
  PlanetFramework/Shader.cpp
  PlanetFramework/Shader.h
  PlanetFramework/Singleton.h
  PlanetFramework/SpriteFont.cpp
  PlanetFramework/SpriteFont.h
  PlanetFramework/stdafx.cpp
  PlanetFramework/stdafx.h
  PlanetFramework/TextRenderer.cpp
  PlanetFramework/TextRenderer.h
  PlanetFramework/Texture.cpp
  PlanetFramework/Texture.h
  PlanetFramework/Time.cpp
  PlanetFramework/Time.h
  PlanetFramework/Transform.cpp
  PlanetFramework/Transform.h
  PlanetFramework/ArgvParser.h
  PlanetFramework/ArgvParser.cpp
  PlanetFramework/PlanetTech/Types/Procedural.h
  PlanetFramework/PlanetTech/Types/Procedural.cpp
  PlanetFramework/StaticDependancies/glad/glad.cpp
  PlanetFramework/StaticDependancies/glad/glad.h
  PlanetFramework/StaticDependancies/glad/stdafx.h
)

# --------------------------- EXTERNAL DEPENDENCIES ---------------------------
include(ExternalProject)

externalproject_add(devil_ext
  GIT_REPOSITORY        "https://github.com/DentonW/DevIL.git"
  GIT_TAG               "v1.8.0"
  SOURCE_SUBDIR         "DevIL"
  INSTALL_COMMAND       ""

  #Enable opengl support
  PATCH_COMMAND patch "DevIL/src-ILUT/CMakeLists.txt"
                      "${CMAKE_SOURCE_DIR}/devil.patch"
)

externalproject_get_property(devil_ext source_dir)
externalproject_get_property(devil_ext binary_dir)
set(devil_include_dir ${source_dir}/DevIL/include)
# To know the directory where the lib is, I need to know the
# architecture of the system...
# So we run uname, grab the output and set the directory as needed
# This is stupid and probably broken
execute_process(COMMAND uname -m OUTPUT_VARIABLE ARCHITECTURE)
if(${ARCHITECTURE} STREQUAL "x86_64\n")
  set(devil_lib_dir ${binary_dir}/lib/x64)
else()
  set(devil_lib_dir ${binary_dir}/lib/x32)
endif()
add_library(il SHARED IMPORTED)
set_property(TARGET il PROPERTY IMPORTED_LOCATION
  ${devil_lib_dir}/libIL.so)
add_library(ilu SHARED IMPORTED)
set_property(TARGET ilu PROPERTY IMPORTED_LOCATION
  ${devil_lib_dir}/libILU.so)
add_library(ilut SHARED IMPORTED)
set_property(TARGET ilut PROPERTY IMPORTED_LOCATION
  ${devil_lib_dir}/libILUT.so)

find_package(glm 0.9.7 QUIET) #Supress package not found warning
if(${glm_FOUND})
  message(STATUS "Found GLM version ${glm_VERSION}")
else()
  message(STATUS "CMake didn't find GLM.")
  if(NOT ${GLM_USE_NATIVE})
    message(WARNING "Will download with make.\n\
If you have GLM installed, you can disable the download by passing \
-DGLM_USE_NATIVE=YES to cmake. Required version is at least 0.9.7")
    externalproject_add(glm_ext
      GIT_REPOSITORY      "https://github.com/g-truc/glm.git"
      GIT_TAG             "0.9.8.5"
      CONFIGURE_COMMAND   ""
      BUILD_COMMAND       ""
      INSTALL_COMMAND     ""
    )
    externalproject_get_property(glm_ext source_dir)
    set(GLM_INCLUDE_DIRS ${source_dir})
  else()
    message(STATUS "Expecting glm to be available in /usr/include.")
  endif()
endif()

find_package(OpenGL 3.3 REQUIRED)
find_package(SDL2 REQUIRED)

# ------------------------------------- # -------------------------------------

# link to directories
add_custom_target(shaders ALL COMMAND ${CMAKE_COMMAND} -E create_symlink
  ${CMAKE_SOURCE_DIR}/PlanetFramework/Shaders Shaders
  COMMENT "Creating symlink to Shaders")
add_custom_target(textures ALL COMMAND ${CMAKE_COMMAND} -E create_symlink
  ${CMAKE_SOURCE_DIR}/PlanetFramework/Textures Textures
  COMMENT "Creating symlink to Textures")
add_custom_target(fonts ALL COMMAND ${CMAKE_COMMAND} -E create_symlink
  ${CMAKE_SOURCE_DIR}/PlanetFramework/Fonts Fonts
  COMMENT "Creating symlink to Fonts")

# Target
add_definitions(-DILUT_USE_OPENGL -DPLATFORM_Linux)
set(EXEC PlanetRenderer)
add_executable(${EXEC} ${SRCS})
# Build this before EXEC
add_dependencies(${EXEC} devil_ext shaders textures)
if((NOT ${glm_FOUND}) AND (NOT ${GLM_USE_NATIVE}))
  add_dependencies(${EXEC} glm_ext)
endif()

# Compile options
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
  if(CMAKE_BUILD_TYPE MATCHES "Debug")
    target_compile_options(${EXEC} PRIVATE
      "-Wall" "-Wpedantic")
  else()
    target_compile_options(${EXEC} PRIVATE "-O3")
  endif()
  if(ASAN)
    set_target_properties(${EXEC} PROPERTIES
      LINK_FLAGS "-fsanitize=address")
  endif()
endif()

#DevIL
target_include_directories(${EXEC} PRIVATE ${devil_include_dir})
target_link_libraries(${EXEC} PRIVATE il ilu ilut)
#GL and GLU
target_link_libraries(${EXEC} PRIVATE ${OPENGL_gl_LIBRARY})
target_link_libraries(${EXEC} PRIVATE ${OPENGL_glu_LIBRARY})
target_include_directories(${EXEC} PRIVATE ${OPENGL_INCLUDE_DIR})
#GLM
target_include_directories(${EXEC} PRIVATE ${GLM_INCLUDE_DIRS})
#SDL
target_link_libraries(${EXEC} PRIVATE ${SDL2_LIBRARIES})
target_include_directories(${EXEC} PRIVATE ${SDL2_INCLUDE_DIRS})

target_include_directories(${EXEC} PRIVATE include)
#Force c++14
target_compile_features(${EXEC} PRIVATE cxx_decltype_auto)

# Add static analysers
if(STATIC_ANALYSIS)
  if(NOT DEFINED CMAKE_CXX_CLANG_TIDY)
    #CMAKE_CXX_CLANG_TIDY was not set
    find_program(clang_tidy_loc clang-tidy)
    if (EXISTS ${clang_tidy_loc})
      message(STATUS "Found clang-tidy at " ${clang_tidy_loc})
      set_target_properties(${EXEC} PROPERTIES
        CXX_CLANG_TIDY "${clang_tidy_loc};-checks=*")
      get_target_property(test ${EXEC} CXX_CLANG_TIDY)
    else()
      message(STATUS "clang-tidy not found")
    endif()
  endif()
  if (NOT DEFINED CMAKE_CXX_CPPCHECK)
    find_program(cppcheck_loc cppcheck)
    if(EXISTS ${cppcheck_loc})
      message(STATUS "Found cppcheck at " ${cppcheck_loc})
      message(STATUS "cppcheck is only available from CMake 3.9 and"
      " higher")
      set_target_properties(${EXEC} PROPERTIES
        CXX_CPPCHECK
        "${cppcheck_loc};--enable=warning,performance,information")
    else()
      message(STATUS "cppcheck not found")
    endif()
  endif()
endif()

# Export documentation, only available if doxygen and doxygen_add_docs
# are available
find_package(Doxygen OPTIONAL_COMPONENTS dot)
if(COMMAND doxygen_add_docs)
  if(${DOXYGEN_FOUND})
    message(STATUS "Found Doxygen, adding doxygen target.")
    set(DOXYGEN_OUTPUT_DIRECTORY doc)

    # Doxygen configuration
    set(DOXYGEN_EXTRACT_ALL YES)
    set(DOXYGEN_CALL_GRAPH YES)
    set(DOXYGEN_CALLER_GRAPH YES)
    if(NOT ${NO_SVG})
      set(DOXYGEN_DOT_IMAGE_FORMAT svg)
      set(DOXYGEN_INTERACTIVE_SVG YES)
    else()
      set(DOXYGEN_DOT_IMAGE_FORMAT png)
    endif()
    #Disable with -DDOXYGEN_ONLY_PUBLIC=YES
    if(NOT DOXYGEN_ONLY_PUBLIC)
      set(DOXYGEN_EXTRACT_PRIVATE YES)
      set(DOXYGEN_EXTRACT_STATIC YES)
    endif()
    # Keep dot files
    if(KEEP_DOT)
      set(DOXYGEN_DOT_CLEANUP NO)
    endif()

    doxygen_add_docs(
      doxygen
      ${SRCS}
      COMMENT "Generate documentation"
    )
  endif()
else()
  message(WARNING "doxygen_add_docs not available, doxygen target\
  disabled. Update CMake.")
endif()
