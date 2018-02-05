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
target_compile_features(${EXEC} PRIVATE cxx_std_14)

find_package(OpenGL 3.3 REQUIRED)
#GL sans GLU
target_link_libraries(${EXEC} ${OPENGL_gl_LIBRARY})
target_include_directories(${EXEC} PRIVATE ${OPENGL_INCLUDE_DIR})

find_package(glfw3 REQUIRED)
target_link_libraries(${EXEC} ${GLFW3_LIBRARY})

find_package(glm REQUIRED)
target_include_directories(${EXEC} PRIVATE ${GLM_INCLUDE_DIR})
