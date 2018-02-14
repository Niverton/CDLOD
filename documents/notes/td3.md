% TD3
% Brian Mazé
% 6 février 2018

#Cahier des besoins

## Intro
Beaucoup d'ambiguïté et manque de présicion
- grille? (alors que l'on utilise maillage(utilisation de 2 termes))
- Sphère? (alors que l'on parle de planète)
- répétition de quelque mots dans une même phrase (appliqué...)

## Etat de l'art
-Citation mal utilisé/ambigue
-"le [strugar(2009)]" => plutot écrire: La méthode de strugar [...]
-OpenGl => OpenGl
-Préciser que l'on ne vise pas Windows mais Linux, que l'on vise OpenGL et pas Directx(pour expliqué pourquoi on ne peux pas reprendre le code fourni)
-Pas assez de précision sur les sources trouvé

## BF

###Interface graphique

- OpenGL = besoin non fonctionnel
- Problème de rédaction
- Présicion sur comment on compte afficher du texte sur OpenGL (librairie? ...)

###Génération de terrain

-Bruit performant? (manque de précision)
-Transformation de Cube à sphère OK mais commment on compte passer de la carte de hauteur au Cube?
-Priorité faible? (alors que l'Interface à une priorité haute)

###Structure de données
-Comment on comptre remplir le QuadTree?
-CDLOD transition pas claire(manque d'explication)
-Cône de vision à redéfinir


## BNF

###Structure de données
-Pourquoi on veut utiliser un float(en quoi il est mieux qu'un autre?)
-Ordre de la centaine de Mo?(A préciser)

###Performance
-Sur quoi ça repose
-60 fps viable?
-Spécifiaction à apporté par rapport au code réutilisable

###Test Unitaire
-Détail sur les tests 

###Robustesse
-Partage des arètes (à préciser)

##Diagramme
-Présicions sur l'articulation entre les tâches à apporté

#Travail pour la release

-Spécifier l'architecture
-API des modules
-Diagramme UML
-Diagramme de séquences
