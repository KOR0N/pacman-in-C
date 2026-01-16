#include "main.h"


int main(int argc, char* argv[])
{

    RendererParameters * params = malloc(sizeof(RendererParameters));
    Textures * textures = malloc(sizeof(Textures));
    init(params, textures, 500, 500, 60);

    SDL_Delay(4000);


    return 0;
}



