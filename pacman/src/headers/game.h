#ifndef GAME_H
#define GAME_H

#include "framework.h"
#include "ghosts.h"
#include "headers/player.h"

typedef struct {
    Player pacman;
    Ghost* ghosts;
    char** level;
    int gommeTimer;
    int dotsCount;
    int points;
    int state; // 0: playing, 1: win, -1: loose
} Game;

/**
 * Initialize the game
 * @param game game variable
 * @param level the current level
 */
void init_game(Game* game, char** level,Textures* textures);

/**
 * Update the game state each frame
 * @param game current game state
 * @param input player input, arrows or esc
 */
void update_game(Game* game, char** level,  int input);

/**
 * Effectively display the game on screen
 * @param game the current game state
 * @param params SDL3 params to use
 * @param textures images to display
 */
void draw_game(const Game* game, const RendererParameters* params, const Textures* textures);

static SDL_Texture* get_ghost_texture(const Ghost* g, const Textures* textures);

#endif
