//
// Created by 20231658 on 03/02/2026.
//

#ifndef PACMAN_PLAYER_H
#define PACMAN_PLAYER_H

typedef struct {
    int x, y;
    int dx, dy;
    int next_dx, next_dy; // For Pacman buffering
    float angle;
} Player;

void move_player(Player* pacman, char** level, int input);

#endif //PACMAN_PLAYER_H