# pacman-in-C

# 🎮 PAC-MAN

Un clone classique du légendaire Pac-Man, développé en C pur. Revivez l'expérience arcade nostalgique directement dans votre terminal !

![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)
![Language](https://img.shields.io/badge/language-C-orange.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

## ✨ Fonctionnalités

- 🕹️ Gameplay fidèle au Pac-Man original
- 👻 Fantômes avec comportements distincts et aléatoire
- 🍒 Power-ups
- 📊 Système de vies (3)

## 🎯 Objectif du jeu

Incarnez Pac-Man et dévorez toutes les pac-gommes du labyrinthe tout en évitant les fantômes. Mangez les super pac-gommes pour inverser les rôles et chasser les fantômes pendant quelques secondes !

## 🎮 Contrôles

```
↑     - Déplacer vers le haut
↓     - Déplacer vers le bas
←     - Déplacer vers la gauche
→     - Déplacer vers la droite
P     - Pause
ESC   - Quitter
```

## 🛠️ Installation

### Sous Linux/macOS

```bash
# Installer les dépendances (Ubuntu/Debian)
sudo apt-get install build-essential libncurses5-dev libncursesw5-dev

# Cloner le projet
git clone https://github.com/votre-username/pacman-c.git
cd pacman-c

# Compiler
make

# Lancer le jeu
./pacman
```

### Sous Windows (avec MinGW)

```bash
# Compiler
gcc -o pacman.exe src/*.c -lncurses

# Lancer
pacman.exe
```

## 📁 Structure du projet

```
pacman-c/
├── src/
│   ├── main.c              # Point d'entrée du programme
│   ├── main.h              # Déclarations principales
│   ├── player.c            # Gestion du joueur (mouvements, collisions)
│   ├── player.h            # En-tête du joueur
│   ├── framework.c         # Framework SDL2 (initialisation, rendu)
│   ├── framework.h         # En-tête du framework
│   ├── firstlevel.c        # Génération et logique du premier niveau
│   ├── firstlevel.h        # En-tête du niveau
│   ├── ghosts.c            # Comportement des fantômes
│   └── ghosts.h            # En-tête des fantômes
├── ressources/
│   └── images/             # Sprites et textures du jeu
│       ├── wall.bmp
│       ├── pacman.bmp
│       ├── dot.bmp
│       └── ...
├── doc/
│   ├── consignes           # Cahier des charges du projet
│   └── SDL_CMOKA_SETUP     # Guide d'installation SDL
├── libs/                   # Bibliothèques externes (Windows)
├── Makefile                # Script de compilation
└── README.md               # Ce fichier
```

## 🎨 Captures d'écran du jeu

```
<img width="586" height="648" alt="image" src="https://github.com/user-attachments/assets/848e4e68-ea9a-4ed2-a0f2-b37d041c9ff8" />
```

## 🐛 Debugging

Pour compiler en mode debug avec les symboles :

```bash
make debug
gdb ./pacman
```

## 📝 TODO

- [ ] Ajouter plus de niveaux
- [ ] Ajouter un score
- [ ] Effets sonores
- [ ] Implémenter un système de sauvegarde des high scores

**Bon jeu ! 🎮👾**
