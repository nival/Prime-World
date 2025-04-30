[English](README.md)        [Русский](README_Russian.md)        [中文](README_Chinese.md)        [हिन्दी](README_Hindi.md)        [Español](README_Spanish.md)        [Français](README_French.md)        [Deutsch](README_German.md)        [Português](README_Portuguese.md)        [日本語](README_Japanese.md)        [Bahasa Indonesia](README_Indonesian.md)

[![Prime World Trailer](PW_trailer.png)](https://youtu.be/Fkd-zva4npI)
[Prime World](https://wikipedia.org/wiki/Prime_World) est un jeu d'arène de bataille en ligne multijoueur (MOBA) sorti en 2014. Le jeu a été développé sur un moteur de jeu interne par la société [Nival](http://nival.com/), principalement écrit en C++.

Le jeu se compose de deux parties : le Château et la partie Combat. Le joueur incarne un Lord ou une Lady. Dans le Château, le joueur construit des bâtiments, engage des Héros et leur choisit des Talents. Dans la partie Combat, le joueur contrôle un Héros et utilise les Talents pour affronter d'autres joueurs lors de combats en équipe.

En 2024, le code source de la partie Combat du jeu a été publié sous une [licence spéciale](LICENSE.md), interdisant toute utilisation commerciale mais totalement ouvert à la communauté du jeu, à des fins d'étude et de recherche.
Veuillez lire attentivement les conditions du [contrat de licence](LICENSE.md) avant toute utilisation.

## Contenu de ce dépôt
- `pw` — le code principal de la partie combat
- `pw_publish` — client compilé de la partie combat avec codes de triche et éditeur client
- `pw/branches/r1117/Bin/PF_Editor.exe` — éditeur de données du jeu

## Préparation
Vous devez télécharger les données de ce dépôt et fusionner le dossier `Bin` avec les données principales du jeu. Voici comment procéder :

1. Copiez le dossier `pw_publish/branch/Client/PvP/Bin` dans `pw/branches/r1117`, en remplaçant les fichiers existants.
2. Lancez le client avec les codes de triche `pw/branches/r1117/Bin/PW_Game.exe`.
3. Si tout est correct, vous verrez la fenêtre de chargement, mais sans image et avec un écran noir.
4. Dans le dossier `Profiles -> game.cfg`, changez la valeur `local_game 0` en `local_game 1`.
5. Relancez le client avec les codes de triche. Vous devriez maintenant voir le lobby où vous pouvez choisir une carte, un héros et démarrer un match.
6. Dans le jeu, appuyez sur la touche Tilde (~) du clavier, et la console pour entrer des codes de triche s'affichera.

En cas d'erreur, consultez les fichiers journaux dans `pw/branches/r1117/Bin/logs`.

## Données du jeu
Les données peuvent être éditées avec l'éditeur situé dans `pw/branches/r1117/Data`

En modifiant les données, vous pouvez :
1. Modifier les descriptions des talents et capacités des héros.
2. Modifier les talents et capacités des héros.
3. Modifier la logique des creeps et des tours.
4. Ajouter de nouveaux héros et capacités.
5. Ajouter de nouveaux talents.
6. Modifier et ajouter des effets.
7. Modifier et ajouter des modèles et des animations.

Après modification des données, il n'est pas nécessaire de recompiler le client à partir du code. Il suffit de cliquer sur `File -> Save` et toutes les modifications apparaîtront instantanément dans le client de jeu `PW_Game`. Par exemple, vous pouvez essayer de modifier la description d'un talent ou d'une capacité de héros.

## Éditeur de données du jeu
L'éditeur de données du jeu se trouve dans `pw/branches/r1117/Bin/PF_Editor.exe`

Lors de la première ouverture de l'éditeur, il faut configurer le chemin vers `Data` :
1. `Tools -> File System Configuration`.
2. `Add -> WinFileSystem`.
3. Définissez le dossier Data comme racine du système : `pw/branches/r1117/Data`.
4. Fermez les fenêtres.
5. Dans l'éditeur : `Views -> Object Browser` et `Views -> Properties Editor`. Ce sont les deux panneaux principaux pour éditer les données.

Les onglets de l'éditeur peuvent être déplacés et ancrés.

## Client du jeu avec codes de triche
Dans le dépôt, vous pouvez trouver le client déjà compilé avec codes de triche `pw_publish/branch/Client/PvP/Bin/PW_Game.exe`

Il est nécessaire que les dossiers `Localization`, `Profiles` et `Data` se trouvent à côté du dossier `Bin`. C'est pourquoi il faut le déplacer dans le dossier `pw` lors de la préparation. En cas de modification du code, une recompilation du client sera nécessaire.

## Comment lancer le PvP
1. Dans `Profiles -> game.cfg`, changez `local_game 0`.
2. Ajoutez `login_adress <server address>`.
3. Lancez le jeu avec le paramètre `-dev_login MonPseudo`.

## Comment lancer le jeu avec des bots
1. Renommez le fichier `Profiles -> private.cfg_example` en `private.cfg`.
2. Ouvrez le fichier avec le Bloc-notes.
3. Cherchez `AT BEGINNING GAME`.
4. Ajoutez une nouvelle ligne : `add_ai bots` — ceci attribuera un bot IA à chaque héros du jeu.

## Résolution des éventuelles erreurs
1. Renommez le fichier `Profiles -> private.cfg_example` en `private.cfg`.
2. Ouvrez le fichier avec le Bloc-notes.
3. Cherchez la section `performance section`.
4. Trouvez la ligne `setvar gfx_fullscreen = 0` — cela lancera le jeu en mode fenêtré, ce qui peut améliorer la stabilité.
5. D'autres réglages d'optimisation peuvent aussi être modifiés dans la `performance section`.

## Remerciements
À la communauté **Prime World: Nova** pour leur contribution à la documentation et à la correction des erreurs.
