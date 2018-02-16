cmake_minimum_required(VERSION 3.7.2)

project(world_gen)

# Fichiers source
set(SRCS
  # Sources src/*
  src/AtmosphereRenderer.cpp
  src/Camera.cpp
  src/ChunkMesh.cpp
  src/COLLADALoader.cpp
  src/DDSLoader.cpp
  src/GameObjectPlaceHolder.cpp
  src/GameTimer.cpp
  src/Geometry.cpp
  src/glApp.cpp
  src/GrassPatch.cpp
  src/GrassRenderer.cpp
  src/HeightmapCache.cpp
  src/HeightmapGenerator.cpp
  src/HeightmapManager.cpp
  #src/LeapControl.cpp
  src/LoadShaders.cpp
  src/main.cpp
  src/MathUtils.cpp
  src/OceanPlane.cpp
  src/ParticleSystem.cpp
  src/RenderableMesh.cpp
  src/SkyboxRenderer.cpp
  src/TerrainLODQuadTree.cpp
  src/TerrainMeshCompute.cpp
  src/TerrainMesh.cpp
  src/TerrainRenderer.cpp
  src/Texture.cpp
  src/TextureManager.cpp
  src/TGALoader.cpp
  src/VoxelChunk.cpp
  src/VoxelRenderer.cpp
  src/VoxelTreeGenerator.cpp
)
set(EXEC world_generator)
add_executable(${EXEC} ${SRCS})
target_include_directories(${EXEC} PRIVATE src)
#Forcer le C++14, cxx_std_14 pas disponible sur la version 3.7 de cmake
target_compile_features(${EXEC} PRIVATE cxx_decltype_auto)

find_package(OpenGL 4.5 REQUIRED)
#GL sans GLU
target_link_libraries(${EXEC} ${OPENGL_gl_LIBRARY})
target_include_directories(${EXEC} PRIVATE ${OPENGL_INCLUDE_DIR})

find_package(glfw3 REQUIRED)
target_link_libraries(${EXEC} glfw)

find_package(glm REQUIRED)

find_package(GLEW REQUIRED)
target_link_libraries(${EXEC} GLEW)

find_package(tinyxml2 REQUIRED)
target_link_libraries(${EXEC} tinyxml2)
