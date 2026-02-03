#include "headers/framework.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// pour construire les chemins de fichiers
const char* pathSeparator =
#ifdef _WIN32
        "\\";
#else
        "/";
#endif

#define ZOOM 1.5
#define GRID_CELL_SIZE 14


void init(RendererParameters *params, Textures *textures, int width, int height, const int fps)
{
    // Initialisation du générateur de nombres pseudo-aléatoires
    srand(time(nullptr));

    // Initialisation de SDL3
    if (!SDL_Init(0)) { // SDL3 doesn't need subsystem flags here
        printf("Framework -> SDL_Init failed: %s\n", SDL_GetError());
        exit(1);
    }

    // Fenêtre
     Uint32 windowFlags = 0;
    if (width == -1 && height == -1) {
        const SDL_DisplayMode *DM = SDL_GetCurrentDisplayMode(SDL_GetPrimaryDisplay());
        width = DM ? DM->w : 800;
        height = DM ? DM->h : 600;
        windowFlags |= SDL_WINDOW_FULLSCREEN;
    }
    else if (width != params->width || height != params->height)
    {
        params->width = width;
        params->height = height;
    }

    // Création de la fenêtre
    params->window = SDL_CreateWindow("Pacman", width, height, windowFlags);
    if (params->window == nullptr) {
        printf("Framework -> SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
    SDL_ShowWindow(params->window);

    // Création du moteur de rendu graphique
    params->renderer = SDL_CreateRenderer(params->window, nullptr);
    if (params->renderer == nullptr) {
        printf("Framework -> SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        SDL_DestroyWindow(params->window);
        exit(1);
    }
    // Try to enable vsync (best-effort)
    SDL_SetRenderVSync(params->renderer, 1);
    // Clear once so the first present shows something
    SDL_SetRenderDrawColor(params->renderer, 0, 0, 0, 255);
    SDL_RenderClear(params->renderer);
    SDL_RenderPresent(params->renderer);

    // Textures de chacun des sprites du jeu
    textures->texturePacman = getTexture("pacman.bmp", params);
    textures->textureWall = getTexture("wall.bmp", params);
    textures->textureDot = getTexture("dot.bmp", params);
    textures->textureSuperPacGum = getTexture("super_pacgum.bmp", params);
    textures->textureBlinky = getTexture("blinky.bmp", params);
    textures->textureBlinkyL = getTexture("blinkyL.bmp", params);
    textures->textureBlinkyU = getTexture("blinkyU.bmp", params);
    textures->textureBlinkyD = getTexture("blinkyD.bmp", params);
    textures->texturePinky = getTexture("pinky.bmp", params);
    textures->texturePinkyL = getTexture("pinkyL.bmp", params);
    textures->texturePinkyU = getTexture("pinkyU.bmp", params);
    textures->texturePinkyD = getTexture("pinkyD.bmp", params);
    textures->textureInky = getTexture("inky.bmp", params);
    textures->textureInkyL = getTexture("inkyL.bmp", params);
    textures->textureInkyU = getTexture("inkyU.bmp", params);
    textures->textureInkyD = getTexture("inkyD.bmp", params);
    textures->textureClyde = getTexture("clyde.bmp", params);
    textures->textureClydeL = getTexture("clydeL.bmp", params);
    textures->textureClydeU = getTexture("clydeU.bmp", params);
    textures->textureClydeD = getTexture("clydeD.bmp", params);
    textures->textureBLue = getTexture("blue.bmp", params);

    textures->cellSize = ZOOM * GRID_CELL_SIZE;

    // Délai de rafraichissement
     params->ticks_for_next_frame = (Uint32)(1000u / (Uint32)fps);
     /* Initialize lastTimeScreenUpdate to the current tick count so the first call
         to update() doesn't print a spurious "FPS too high" warning caused by
         comparing against a 0 initial value. */
     params->lastTimeScreenUpdate = SDL_GetTicks();
}

void initWindowed(RendererParameters *params, Textures *textures)
{
    params->width = (int)(WIDTH * ZOOM * GRID_CELL_SIZE);
    params->height = (int)(HEIGHT * ZOOM * GRID_CELL_SIZE);
    init(params, textures, params->width, params->height, FPS);
}


int getInput(void) {
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
        if (e.type == SDL_EVENT_QUIT) {
            return SDL_EVENT_QUIT;
        }
        if (e.type == SDL_EVENT_KEY_DOWN) {
            return (int)e.key.key; // SDL3: use 'key' (SDL_Keycode)
        }
    }
    return 0;
}

void update(RendererParameters *params) {
    // On attend le temps nécessaire pour atteindre le taux de FPS
    int nbTicksWait = 0;
    Uint32 now = SDL_GetTicks();
    while (now - params->lastTimeScreenUpdate < params->ticks_for_next_frame) {
        SDL_Delay(1);
        nbTicksWait++;
        now = SDL_GetTicks();
    }

    /* Only print the warning when we actually have a valid previous timestamp.
       This avoids an incorrect warning on the very first frame. */
    if (params->lastTimeScreenUpdate != 0u && nbTicksWait == 0)
        printf("Warning, FPS too high, lagged for %u ms\n", (unsigned)(now - params->lastTimeScreenUpdate));

    // On met à jour l'écran
    SDL_RenderPresent(params->renderer);
    SDL_SetRenderDrawColor(params->renderer, 0, 0, 0, 0);
    SDL_RenderClear(params->renderer);

    // On réarme le temps d'attente pour le prochain rafraichissement
    params->lastTimeScreenUpdate = SDL_GetTicks();
}

void drawSprite(SDL_Texture* texture, const int x, const int y, const float angle, const RendererParameters* params)
{
    // keep existing sizing logic (grid size)
    const SDL_FRect dest = { (float)(x * GRID_CELL_SIZE * ZOOM), (float)(y * GRID_CELL_SIZE * ZOOM),
                       (float)(GRID_CELL_SIZE * ZOOM), (float)(GRID_CELL_SIZE * ZOOM) };
    if (!SDL_RenderTextureRotated(params->renderer, texture, nullptr, &dest, (double)angle, nullptr, SDL_FLIP_NONE))
        printf("DrawSprite -> SDL_RenderTextureRotated failed: %s\n", SDL_GetError());
}

// Match framework.h: void drawSpriteOnGrid(SDL_Texture * texture, int x, int y, float angle, RendererParameters *params);
void drawSpriteOnGrid(SDL_Texture * texture, const int x, const int y, const float angle, const RendererParameters *params) {
    const float cell = GRID_CELL_SIZE * ZOOM;
    const SDL_FRect dest = { ((float)x * cell), ((float)y * cell), cell, cell };
    if (!SDL_RenderTextureRotated(params->renderer, texture, nullptr, &dest, (double)angle, nullptr, SDL_FLIP_NONE))
        printf("DrawSpriteOnGrid -> SDL_RenderTextureRotated failed: %s\n", SDL_GetError());
}

void drawLevel(char** level, const RendererParameters *params, const Textures *textures)
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            switch (level[i][j])
            {
            case 'H':
                drawSpriteOnGrid(textures->textureWall, j, i, 0, params);
                break;
            case '.':
                drawSpriteOnGrid(textures->textureDot, j, i, 0, params);
                break;
            case 'G':
                drawSpriteOnGrid(textures->textureSuperPacGum, j, i, 0, params);
                break;
            case ' ':
            case 'O':
            case 'P':
            case 'I':
            case 'C':
            case 'B':
              // L'affichage de pacman et des fantomes n'est pas gere ici.
            break;

            default:
                printf("ERROR: Wrong element in the given level : %c\n", level[i][j]);
            }
        }
    }
}

void drawLevelPoints(const RendererParameters *params, int points) {
    char text[50];
    sprintf(text, "%d", points);
    SDL_SetRenderDrawColor(params->renderer, 255, 255, 0, 255); // Yellow
    SDL_RenderDebugText(params->renderer, 10, 10, text);
}

int drawMenuLevelSelect(const RendererParameters *params)
{
    int selected = 0;
    SDL_Event e;
    float mouseX, mouseY;

    // Define buttons
    float btnWidth = 200.0f;
    float btnHeight = 50.0f;
    float centerX = params->width / 2.0f;
    float centerY = params->height / 2.0f;

    SDL_FRect btn1 = { centerX - btnWidth/2, centerY - 60, btnWidth, btnHeight };
    SDL_FRect btn2 = { centerX - btnWidth/2, centerY + 10, btnWidth, btnHeight };

    while (selected == 0) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                return -1;
            }
            if (e.type == SDL_EVENT_KEY_DOWN) {
                if (e.key.key == SDLK_ESCAPE) {
                    return -1;
                }
                if (e.key.key == SDLK_1 || e.key.key == SDLK_KP_1) {
                    selected = 1;
                }
                if (e.key.key == SDLK_2 || e.key.key == SDLK_KP_2) {
                    selected = 2;
                }
            }
            if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                 if (e.button.button == SDL_BUTTON_LEFT) {
                     SDL_GetMouseState(&mouseX, &mouseY);
                     SDL_FPoint fPoint = { mouseX, mouseY };
                     if (SDL_PointInRectFloat(&fPoint, &btn1)) selected = 1;
                     if (SDL_PointInRectFloat(&fPoint, &btn2)) selected = 2;
                 }
            }
        }

        SDL_GetMouseState(&mouseX, &mouseY);
        SDL_FPoint fMouse = { mouseX, mouseY };

        SDL_SetRenderDrawColor(params->renderer, 0, 0, 0, 255);
        SDL_RenderClear(params->renderer);

        // Draw Title
        SDL_SetRenderDrawColor(params->renderer, 255, 255, 0, 255); // Yellow
        SDL_RenderDebugText(params->renderer, centerX - 40, centerY - 120, "PACMAN - SELECT LEVEL");

        // Draw Button 1
        if (SDL_PointInRectFloat(&fMouse, &btn1)) {
            SDL_SetRenderDrawColor(params->renderer, 50, 50, 200, 255); // Hover color
        } else {
            SDL_SetRenderDrawColor(params->renderer, 0, 0, 150, 255); // Normal color
        }
        SDL_RenderFillRect(params->renderer, &btn1);

        // Border for Button 1
        SDL_SetRenderDrawColor(params->renderer, 255, 255, 255, 255);
        SDL_RenderRect(params->renderer, &btn1);

        SDL_SetRenderDrawColor(params->renderer, 255, 255, 255, 255);
        SDL_RenderDebugText(params->renderer, btn1.x + 70, btn1.y + 18, "LEVEL 1");

        // Draw Button 2
        if (SDL_PointInRectFloat(&fMouse, &btn2)) {
            SDL_SetRenderDrawColor(params->renderer, 50, 50, 200, 255); // Hover color
        } else {
            SDL_SetRenderDrawColor(params->renderer, 0, 0, 150, 255); // Normal color
        }
        SDL_RenderFillRect(params->renderer, &btn2);

        // Border for Button 2
        SDL_SetRenderDrawColor(params->renderer, 255, 255, 255, 255);
        SDL_RenderRect(params->renderer, &btn2);

        SDL_SetRenderDrawColor(params->renderer, 255, 255, 255, 255);
        SDL_RenderDebugText(params->renderer, btn2.x + 70, btn2.y + 18, "LEVEL 2");

        SDL_RenderPresent(params->renderer);
        SDL_Delay(10);
    }
    return selected;
}


// Création d'une texture de sprite
// --------
// * imgName : nom du fichier de l'image (format BMP avec alpha)
SDL_Texture * getTexture(char* imageName, const RendererParameters *params)
{
    char imagePath[256];
    /* Build path: resources/<sep>/images/<sep>/<imageName> */
    const int written = snprintf(imagePath, sizeof(imagePath), "resources%simages%s%s", pathSeparator, pathSeparator, imageName);
    if (written < 0 || written >= (int)sizeof(imagePath)) {
        printf("GetTexture -> image path too long\n");
        exit(1);
    }
    SDL_Surface * sprite = SDL_LoadBMP(imagePath);

    if (!sprite) {
        printf("SDL_LoadBMP failed: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_Texture * texture = SDL_CreateTextureFromSurface(params->renderer, sprite);
    if (!texture) {
        printf("GetTexture -> SDL_CreateTextureFromSurface failed: %s\n", SDL_GetError());
        SDL_DestroySurface(sprite);
        exit(1);
    }
    SDL_DestroySurface(sprite);
    return texture;
}

int getRandomNumber() {
    return rand();
}

void cleanUp(const RendererParameters *params, char** level)
{

    if (level)
    {
        for (int i = 0; i < HEIGHT; i++)
        {
            if (level[i]) free(level[i]);
        }
        free(level);
    }

    if (params) {
        if (params->renderer) SDL_DestroyRenderer(params->renderer);
        if (params->window) SDL_DestroyWindow(params->window);
    }
    SDL_Quit();
}
