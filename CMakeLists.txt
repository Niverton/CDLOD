cmake_minimum_required(VERSION 3.7.2)

project(cdlod)

# Fichiers source
set(SRCS
  # Headers include/*

  # Sources src/*
  src/main.cpp
)
set(EXEC cdlod_viewer)
add_executable(${EXEC} ${SRCS})
#Forcer le C++14, cxx_std_14 pas disponible sur la version 3.7 de cmake
target_compile_features(${EXEC} PRIVATE cxx_decltype_auto)

find_package(OpenGL 3.3 REQUIRED)
#GL sans GLU
target_link_libraries(${EXEC} ${OPENGL_gl_LIBRARY})
target_include_directories(${EXEC} PRIVATE ${OPENGL_INCLUDE_DIR})

find_package(glfw3 REQUIRED)
target_link_libraries(${EXEC} ${GLFW3_LIBRARY})

find_package(glm)
if(${glm_FOUND})
  target_include_directories(${EXEC} PRIVATE ${GLM_INCLUDE_DIR})
else()
  include(ExternalProject)
  ExternalProject_Add(glm_ext
    GIT_REPOSITORY      "https://github.com/g-truc/glm.git"
    GIT_TAG             "0.9.8.5"
    CONFIGURE_COMMAND   ""
    BUILD_COMMAND       ""
    INSTALL_COMMAND     ""
  )
  ExternalProject_Get_Property(glm_ext source_dir)
  set(GlmIncludeDir ${source_dir})
  target_include_directories(${EXEC} PRIVATE ${GlmIncludeDir})
endif()
