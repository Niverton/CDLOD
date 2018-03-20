# Notes

``` sh
valgrind --tool=callgrind ./PlanetRenderer
```

- Ecrit les resultats du profilage dans un fichier "callgrind.out.xxx"
- Logiciel utilisé pour lire les resultats : kcachegrind

## Notes version stock

### profilage

- Fonction très couteuse en ressources :
  - init (1x)
  - Update (3218x)
    - GenerateGeometry (3218x)
      - RecurciveTriangle (164414x + 436187x) (rec)

### compilation gcc (-Wall -Werror -pedantic)

  - Erreur de pragma (version windows)
  - Variables déclarées initialisées dans un ordre différent. (dans Camera, Tri, TexRenderer, SpriteFont)
