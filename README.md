# PlanetRenderer

Ce projet a été repris dans le cadre de l'UE de Projet de Programmation
du Master Informatique de l'Université de Bordeaux en 2018. L'objectif
de ce projet était d'implémenter l'algorithme de CDLOD de F. Strugar,
proposé dans son papier "*Continuous Distance-Dependent Level of Detail
for Rendering Heightmaps*" publié en 2009.

Le projet repris est celui de Robert Lindner (alias *Illation*),
distribué sous license MIT. Le projet original est disponible
[ici](https://github.com/Illation/PlanetRenderer), une copie du README
original est disponible dans ce dépot sous le nom de README_old.

# Compilation

Ce projet n'a été testé que sous Linux.

## Dépendances

Ce projet nécessite les dépendances suivantes:
- CMake 3.5.1
- OpenGL 3.3
- SDL 2
- GLM 0.9.8.5
- DevIL 1.8.0
- Un compilateur C++ supportant le standard C++14

CMake téléchargera automatiquement DevIL à la compilation, ainsi que GLM
si la bibliothèque n'a pas été trouvée.

La génération de la documentation nécessite Doxygen (ainsi que graphviz
pour les graphes) et une version de CMake égale ou supérieur à 3.9.6.

## Compilation

```sh
mkdir build
cd build
cmake ..
make -j4
```

Les variables CMake suivantes peuvent être modifiées à la configuration
en passant l'option `-D<VARIABLE>=<VALEUR>`:
- GLM_USE_NATIVE (NO): Désactive le téléchargement de GLM
- NO_SVG (NO): Exporter les graphes Doxygen au format PNG
- ASAN (NO): Active l'*address sanitizer* à la compilation
- SANAL (NO): Active les analyseurs statiques à la compilation


# Utilisation

## Options

```sh
-> % ./PlanetRenderer -h
Usage: ./PlanetRenderer
For non procedural run on Earth or Moon: just type MOON/EARTH

For procedurals runs:

 <NOISE> --<noise-option>=<value> --<option>

option:
         -h  --help             show this page.
             --fullscreen       start program in fullscreen.
             --use-vsync        start program with vsync.

<NOISE> --<noise-option>=<value>
Order of options does not matter.
if you set a flag with a wrong noise, it will be ignored

Common options                     Default value
         --width=UInt                    1024
         --height=UInt                   1024
         --max_height=Float              10.0

SIMPLEX
        <common-options>

RIDGEG-NOISE
        <common-options>

FLOW-NOISE
        <common-options>
        --angle=Float                    0.5

FBM
        <common-options>
        --octave=UInt                    4
        --lacunarity=Float               2.0
        --gain=Float                     0.5

WARPED-FBM
        <common-options>
        --octave=UInt                    4
        --lacunarity=Float               2.0
        --gain=Float                     0.5

DFBM-WARPED-FBM
        --octave=UInt                    4
        --lacunarity=Float               2.0
        --gain=Float                     0.5

RIDGED-MULTI-FRACTAL
        <common-options>
        --octave=UInt                    4
        --lacunarity=Float               2.0
        --gain=Float                     0.5

```

## Controles

- F2: désactive le texte
- Z - S: change l'altitude de la caméra
- Q - D: Change la latitude de la caméra
- NUM4 - NUM6: Change le champs de vision de la caméra
- W: Affichage fil de fer
- Flèches Haut et Bas: Change le niveau de détail maximum
- Clique gauche: orienter la caméra
- R: Rotation automatique


