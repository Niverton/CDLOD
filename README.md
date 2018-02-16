# Projet de programmation

## Introduction

Deux approches ont été proposées, développer une application de zéros et
s'en tenir au cahier des besoins rédigé plus tôt, ou reprendre et
adapter le code déjà existant du projet WorldGenerator. L'adaptation du
projet WorldGenerator se trouve dans le dossier 'worldgen', avec un
README explicatif.

## Développer à partir de zéro
L'application à été développé en OpenGL 3.3 core.

### Dépendance

- [glm](http://glm.g-truc.net/0.9.8/index.html)
- [glfw3](http://www.glfw.org/)
- [glew](http://glew.sourceforge.net/)

### Compilation
``` sh
mkdir build && cd build
cmake .. && make -j6
```
Il faut copier à la main les shaders dans le bon répertoire
``` sh
cp -r ../shaders .
```

Pour lancer l'application
``` sh
./cdlod_viewer
```
### Control
Utiliser les fleches du clavier pour déplacer la camera.
La gestion de son orientation n'est pas encore prise en charge.

### Bug connu
Sur certains pc du cremi, les controles ne fonctionnent pas.


