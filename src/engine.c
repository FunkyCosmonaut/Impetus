#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <glad/glad.h>
#include "engine.h"



int Engine_initWindow()
{

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        //std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (win == NULL) {
      //std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL) {
        SDL_DestroyWindow(win);
        //std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Keep the window open for 3 seconds
    SDL_Delay(3000);

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
