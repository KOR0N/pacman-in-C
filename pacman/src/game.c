#include "headers/game.h"
#include <stdlib.h>
#include "headers/player.h"
#include "headers/ghosts.h"

static int is_wall(const char cell) {
    return cell == 'H';
}

static int is_walkable(const char cell) {
    return !is_wall(cell);
}

void init_game(Game* game, char** level,Textures* textures) {
    game->level = level;
    game->gommeTimer = 0;
    game->dotsCount = 0;
    game->points = 0;
    game->state = 0;
    game->ghosts = malloc(sizeof(Ghost*)*4);
    int index=0;

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            const char c = level[y][x];
            if (c == 'O') {
                game->pacman.x = x;
                game->pacman.y = y;
                game->pacman.dx = -1;
                game->pacman.dy = 0;
                game->pacman.next_dx = -1;
                game->pacman.next_dy = 0;
                game->pacman.angle = 0;
            } else if (c == 'C'|| c == 'P' || c == 'I' || c == 'B') {
                game->ghosts[index].x = x;
                game->ghosts[index].y = y;
                if (c =='C') {
                    game->ghosts[index].id = CLYDE;
                } else if (c == 'P') {
                    game->ghosts[index].id = PINKY;
                } else if (c == 'I') {
                    game->ghosts[index].id = INKY;
                } else if (c == 'B') {
                    game->ghosts[index].id = BLINKY;
                }
                index++;
            }
            if (c == '.'){game->dotsCount++;}
        }
    }
}

void draw_game(const Game* game, const RendererParameters* params,const Textures* textures) {
    drawLevel(game->level, params, textures);

    drawSpriteOnGrid(textures->texturePacman, game->pacman.x, game->pacman.y, game->pacman.angle, params);
    for (int i = 0; i < 4; i++) {
        Ghost* g = &game->ghosts[i];
        if (game->gommeTimer == 0) {
            SDL_Texture* tex = get_ghost_texture(g, textures);
            drawSpriteOnGrid(tex, g->x, g->y, 0, params);
        }
        else {
            drawSpriteOnGrid(textures->textureBLue, g->x, g->y, 0, params);
        }
    }
    drawLevelPoints(params, game->points);
}

void update_game(Game* game, char** level, int input) {
    // Sauvegarder les positions actuelles
    int old_pacman_x = game->pacman.x;
    int old_pacman_y = game->pacman.y;

    int old_ghosts_x[4];
    int old_ghosts_y[4];
    for (int i = 0; i < 4; i++) {
        old_ghosts_x[i] = game->ghosts[i].x;
        old_ghosts_y[i] = game->ghosts[i].y;
    }

    // Déplacements
    move_player(&game->pacman, game->level, input);
    move_ghosts(game->ghosts, game->level);

    // Gestion des points et power-ups
    char cell = level[game->pacman.y][game->pacman.x];
    if (cell == '.') {
        game->dotsCount--;
        game->points += 5;
        level[game->pacman.y][game->pacman.x] = ' ';
    } else if (cell == 'G') {
        game->gommeTimer = 40;
        level[game->pacman.y][game->pacman.x] = ' ';
    }

    // Vérification des collisions
    for (int i = 0; i < 4; i++) {
        // Collision même case
        int same_pos = (game->pacman.y == game->ghosts[i].y &&
                       game->pacman.x == game->ghosts[i].x);

        // Collision croisement (échange de positions)
        int crossing = (game->pacman.y == old_ghosts_y[i] &&
                       game->pacman.x == old_ghosts_x[i] &&
                       old_pacman_y == game->ghosts[i].y &&
                       old_pacman_x == game->ghosts[i].x);

        if (same_pos || crossing) {
            if (game->gommeTimer == 0) {
                game->state = -1;
            } else {
                game->ghosts[i].x = 14;
                game->ghosts[i].y = 14;
                game->points += 100;
            }
        }
    }

    if (game->gommeTimer > 0) game->gommeTimer--;
}

static SDL_Texture* get_ghost_texture(const Ghost* g, const Textures* textures)
{
    switch (g->id) {

        case PINKY:
            if (g->dx == -1) return textures->texturePinkyL;
            if (g->dy == -1) return textures->texturePinkyU;
            if (g->dy ==  1) return textures->texturePinkyD;
            return textures->texturePinky;

        case BLINKY:
            if (g->dx == -1) return textures->textureBlinkyL;
            if (g->dy == -1) return textures->textureBlinkyU;
            if (g->dy ==  1) return textures->textureBlinkyD;
            return textures->textureBlinky;

        case INKY:
            if (g->dx == -1) return textures->textureInkyL;
            if (g->dy == -1) return textures->textureInkyU;
            if (g->dy ==  1) return textures->textureInkyD;
            return textures->textureInky;

        case CLYDE:
            if (g->dx == -1) return textures->textureClydeL;
            if (g->dy == -1) return textures->textureClydeU;
            if (g->dy ==  1) return textures->textureClydeD;
            return textures->textureClyde;
    }

    return NULL;
}

