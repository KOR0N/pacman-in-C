#ifndef PACMAN_LEVEL_H
#define PACMAN_LEVEL_H

typedef struct
{
    char **grid;
    int width;
    int height;
    int id;
} Level;

/**
 * Allocate memory for a level
 * @param id The level id
 * @return a playable level
 */
Level loadLevel(int id);

#endif //PACMAN_LEVEL_H