# CRAPS

******Jeu de casino CRAPS écrit en C :
Version sans interface graphique avec une gestion de **dynamique** de la mémoire et des sauvegardes de scores.******


### Utilisation

****Se joue interactivement sur le terminal :****

```sh
$ gcc play_craps.c -o play.craps
$ ./play.craps
```

#### Sauvegarde

Sauvegarde dans un fichier "scores.csv" dans le dossier courant.
le créer s'il n'existe pas *(i.e première partie)*
le charge lorsqu'il existe

#### Règles

[Règles du jeu](RRhttps://www.casino-zen.com/regles-craps/) implémentées.
Peut se jouer seul ou à plusieurs.

