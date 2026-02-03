/*
 * Special thanks to Brewen DL for SDL2/SDL3 migration
*/

#pragma once

#include <SDL3/SDL.h>

#define FPS 10
#define WIDTH 28
#define HEIGHT 31

typedef struct RendererParameters RendererParameters;
struct RendererParameters
{
    SDL_Window *   window;
    SDL_Renderer * renderer;
    Uint32 ticks_for_next_frame;
    Uint32 lastTimeScreenUpdate;
    int width;
    int height;
};

typedef struct Textures Textures;
struct Textures
{
    SDL_Texture * texturePacman;
    SDL_Texture * textureWall;
    SDL_Texture * textureDot;
    SDL_Texture * textureSuperPacGum;
    SDL_Texture * textureBlinky;
    SDL_Texture * textureBlinkyL;
    SDL_Texture * textureBlinkyU;
    SDL_Texture * textureBlinkyD;
    SDL_Texture * texturePinky;
    SDL_Texture * texturePinkyL;
    SDL_Texture * texturePinkyU;
    SDL_Texture * texturePinkyD;
    SDL_Texture * textureInky;
    SDL_Texture * textureInkyL;
    SDL_Texture * textureInkyU;
    SDL_Texture * textureInkyD;
    SDL_Texture * textureClyde;
    SDL_Texture * textureClydeL;
    SDL_Texture * textureClydeU;
    SDL_Texture * textureClydeD;
    SDL_Texture * textureBLue;
    int cellSize;
};

/**
 * Create the initial window
 * @param params SDL3 params to use
 * @param textures images to display
 */
void initWindowed(RendererParameters *params, Textures *textures);

/**
 * Get player input (see more at https://wiki.libsdl.org/SDL3/SDL_Keycode)
 * @return keyboard code || SDL_EVENT_QUIT
 */
int getInput();

/**
 * Update the SDL3 state each frame
 * @param params SDL3 params to use
 */
void update(RendererParameters *params);

/**
 *
 * @param texture sprite texture
 * @param x position in grid
 * @param y position in grid
 * @param angle of rotation of the sprite
 * @param params SDL3 params
 */
void drawSpriteOnGrid(SDL_Texture * texture, int x, int y, float angle, const RendererParameters *params);

/**
 *
 * @param level selected level
 * @param params SDL3 params to use
 * @param textures images to display
 */
void drawLevel(char** level, const RendererParameters *params, const Textures *textures);

/**
 * Display the current score/points on the screen
 * @param params SDL3 params to use
 * @param points number of points to display
 */
void drawLevelPoints(const RendererParameters *params, int points);
/**
 * Main menu to display select level
 * @param params SDL3 params to use
 * @return selected level
 */
int drawMenuLevelSelect(const RendererParameters *params);

/**
 * Converts an image to a texture
 * @param imageName original image
 * @param params SDL3 params to apply
 * @return an SDL3 texture
 */
SDL_Texture * getTexture(char* imageName, const RendererParameters *params);

/**
 * This is responsible for the randomization of ghosts movements
 * @return pseudo-random number
 */
int getRandomNumber();

/**
 * Free the resources, call this function at the end of the program
 * @param params SDL3 params
 * @param level to clean up
 */
void cleanUp(const RendererParameters *params, char** level);

#ifdef PACMAN_TESTS
// ==== API de test (mock framework) ====
void fw_test_setup(void);
void fw_test_set_inputs(const int *keys, int count);
void fw_test_get_pacman(int *x, int *y);
void fw_test_get_ghost(int index, int *x, int *y);
void fw_test_set_level(char **level);
char **fw_test_get_level(void);
char **fw_test_get_drawn_level(void);
int fw_test_get_draw_count(void);
int fw_test_get_round_count(void);
int fw_test_get_blue_draws(void);
float fw_test_get_pacman_angle(void);
char fw_test_get_ghost_last_dir(int index);
void fw_test_teardown(void);
#endif
