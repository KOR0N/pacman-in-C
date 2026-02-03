#include "headers/framework.h"
#include "headers/ghosts.h"

void move_ghosts(Ghost* ghosts, char** level)
{
    for (int i = 0; i < 4; i++) {

        // Directions possibles : haut, bas, droite, gauche
        int directions[4][2] = {
            { 0, -1},
            { 0,  1},
            { 1,  0},
            {-1,  0}
        };

        int r = getRandomNumber() % 4;

        while (1) {
            // Calculer la position de test avec wrap-around
            int test_x = ghosts[i].x + directions[r][0];
            int test_y = ghosts[i].y + directions[r][1];

            // Gestion des tunnels pour le test
            if (test_x < 0) test_x = WIDTH - 1;
            if (test_x >= WIDTH) test_x = 0;
            if (test_y < 0) test_y = HEIGHT - 1;
            if (test_y >= HEIGHT) test_y = 0;

            // Vérifier demi-tour et collision
            int is_opposite = (directions[r][0] == -ghosts[i].dx &&
                              directions[r][1] == -ghosts[i].dy);
            int is_wall = (level[test_y][test_x] == 'H');

            if (!is_opposite && !is_wall) {
                break;  // Direction valide trouvée
            }

            r = getRandomNumber() % 4;
        }

        // Direction validée
        ghosts[i].dx = directions[r][0];
        ghosts[i].dy = directions[r][1];

        int nx = ghosts[i].x + ghosts[i].dx;
        int ny = ghosts[i].y + ghosts[i].dy;

        // Wrap de la map du level
        if (nx < 0) nx = WIDTH - 1;
        if (nx >= WIDTH) nx = 0;
        if (ny < 0) ny = HEIGHT - 1;
        if (ny >= HEIGHT) ny = 0;

        ghosts[i].x = nx;
        ghosts[i].y = ny;
    }
}
