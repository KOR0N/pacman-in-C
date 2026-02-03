#ifndef PACMAN_GHOSTS_H
#define PACMAN_GHOSTS_H

typedef enum
{
    CLYDE = 0,
    PINKY = 1,
    INKY = 2,
    BLINKY = 3,
} ghost_id;

typedef struct {
    int x, y;
    int dx, dy;
    ghost_id id;
    SDL_Texture* text;
} Ghost;

void move_ghosts(Ghost* ghosts, char** level);

#endif //PACMAN_GHOSTS_H