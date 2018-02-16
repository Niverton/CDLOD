# PDP

Le projet a été porté sous Linux et le système de build changé pour
cmake. L'objectif était de voir si le projet était viable comme base.

## Build

```sh
mkdir build && cd build
cmake .. && cmake --build . -- -j4
```

## Dépendances

OpenGL 4.5
GLFW3
GLM
GLEW
TinyXML2

# Readme original

World-Generator
===============

A procedural planet generator made in OpenGL 4.4

This is a project that I worked on over the course of 2 months while learning OpenGL. I have made a few blog posts on leifnode.com describing how the terrain generation works. 

I plan to update terrain generation and ocean rendering within a few months to look better, have biomes, and generate/render more efficiently. 

Controls
---------------
AWSD movement
Left click and drag mouse to look around
Right click to toggle speed adjust mode
  Hold W in speed adjust mode to move faster
  Hold S to move slower
Hold Z or X to change sun angle
Press 1 to toggle wireframe
Press 2 to toggle backface culling


This project also has some leftover/WIP code such as a COLLADA model loader, compute particle system, and geometry shader grass renderer.
