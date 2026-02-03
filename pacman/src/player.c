#include <headers/player.h>
#include <headers/framework.h>

void move_player(Player* pacman, char** level, int input) {

  if (input == SDLK_UP)        { pacman->next_dx = 0;  pacman->next_dy = -1; }
  else if (input == SDLK_DOWN) { pacman->next_dx = 0;  pacman->next_dy = 1; }
  else if (input == SDLK_LEFT) { pacman->next_dx = -1; pacman->next_dy = 0; }
  else if (input == SDLK_RIGHT){ pacman->next_dx = 1; pacman->next_dy = 0; }

  // Vérification de la prochaine direction avec wrap-around
  int test_x = pacman->x + pacman->next_dx;
  int test_y = pacman->y + pacman->next_dy;

  // Gestion des tunnels pour le test
  if (test_x < 0) test_x = WIDTH - 1;
  if (test_x >= WIDTH) test_x = 0;
  if (test_y < 0) test_y = HEIGHT - 1;
  if (test_y >= HEIGHT) test_y = 0;

  if (level[test_y][test_x] != 'H') {
    pacman->dx = pacman->next_dx;
    pacman->dy = pacman->next_dy;
  }

  // Calcul de la nouvelle position
  int nx = pacman->x + pacman->dx;
  int ny = pacman->y + pacman->dy;

  // Gestion des tunnels
  if (nx < 0) nx = WIDTH - 1;
  if (nx >= WIDTH) nx = 0;
  if (ny < 0) ny = HEIGHT - 1;
  if (ny >= HEIGHT) ny = 0;

  // Vérification collision et déplacement
  if (level[ny][nx] != 'H') {
    pacman->x = nx;
    pacman->y = ny;
  }

  // Gestion de l'angle d'affichage
  if (pacman->dx == 1) pacman->angle = 180;
  else if (pacman->dx == -1) pacman->angle = 0;
  else if (pacman->dy == 1) pacman->angle = 270;
  else if (pacman->dy == -1) pacman->angle = 90;
}