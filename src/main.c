#include "main.h"
#include <stdio.h>
#include "firstLevel.h"
#include "framework.h"
#include <SDL3/SDL.h>
#include <stdlib.h>
#include "ghosts.h"
#include "player.h"


int gameLoop(void)
{
    RendererParameters params;
    Textures textures;

    // Initialisation du framework
    initWindowed(&params, &textures);

    char **level = loadFirstLevel();
    int rows = 31;
    int cols = 28;

    int x;
    int y;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (level[i][j]=='O') {
                x=j;
                y=i;
            }
        }
    }

    Player player = createPlayer(&textures,x,y,180);


    Entity ghosts[4];
    int ghostCount = loadEntity(level, ghosts, &textures, rows, cols);

    int prevPlayerX;
    int prevPlayerY;
    int prevGhostX[4];
    int prevGhostY[4];

    for (int i = 0; i < ghostCount; i++) {
        prevGhostX[i] = ghosts[i].posx;
        prevGhostY[i] = ghosts[i].posy;
    }


    int input;
    while (1) {

        input = getInput();
        drawLevel(level, &params, &textures);

        prevPlayerX = player.x;
        prevPlayerY = player.y;
        for (int i = 0; i < ghostCount; i++) {
            prevGhostX[i] = ghosts[i].posx;
            prevGhostY[i] = ghosts[i].posy;
        }

        for (int i = 0; i < ghostCount; i++) {
            moveEntity(&ghosts[i], level, rows, cols);
            drawEntity(&ghosts[i], &params, &textures);
        }

        movePlayer(&player, level, input, cols);
        drawPlayer(&player,&params);


        SDL_Delay(60);

        for (int i = 0; i < ghostCount; i++) {
            // Collision croisé
            if (prevGhostX[i] == player.x && prevGhostY[i] == player.y &&
                prevPlayerX == ghosts[i].posx && prevPlayerY == ghosts[i].posy // ils se croisent
               ){
                SDL_Delay(600);
                cleanUp(&params,level);
                return 0;
               }
        }

        update(&params);

        for (int i = 0; i < ghostCount; i++) {
            // Collision directe
            if (ghosts[i].posx == player.x && ghosts[i].posy == player.y) {
                SDL_Delay(600);
                cleanUp(&params,level);
                return 0;
            }
        }

        if (input == SDLK_ESCAPE) {
            SDL_Delay(600);
            cleanUp(&params,level);
            return 0;
        }
    }
}

#ifndef PACMAN_TESTS
int main(void)
{
    gameLoop();
    return 0;
}
#endif
