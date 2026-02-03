#include "headers/main.h"
#include "headers/firstLevel.h"
#include "headers/framework.h"
#include "headers/game.h"
#include "headers/level.h"
#include <SDL3/SDL.h>
#include <stdio.h>

int gameLoop(void)
{
    RendererParameters params;
    Textures textures;
    Game game;

    // Initialisation du framework
    initWindowed(&params, &textures);

    int selectedLevel = drawMenuLevelSelect(&params);
    if (selectedLevel == -1) {
        cleanUp(&params, nullptr);
        return 0;
    }
    const Level levelStruct = loadLevel(selectedLevel);
    char** level = levelStruct.grid;
    //char** level = loadFirstLevel();

    init_game(&game, level,&textures);

    int quit = 0;
    while (!quit) {
        const int input = getInput();
        if (input == SDL_EVENT_QUIT || input == SDLK_ESCAPE) {
            quit = 1;
            break;
        }

        update_game(&game, level, input);
        draw_game(&game, &params, &textures);
        update(&params);

        if (game.state != 0) {
            quit = 1;
        }
    }

    //cleanUp(&params, level);

    if (game.state == 1) return 1;
    if (game.state == -1) return -1;
    return 0;
}

#ifndef PACMAN_TESTS
int main(void)
{
    gameLoop();
    return 0;
}
#endif
