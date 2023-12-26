#include <SDL2/SDL.h>
#include "video.h"

const int SCREEN_WIDTH = 64;
const int SCREEN_HEIGHT = 32;
const int SCREEN_SCALE = 16;

Video init_video() {
    Video video;
    video.window = NULL;
    video.surface =  NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(-1);
    }

    video.window = SDL_CreateWindow("CHIP8",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH * SCREEN_SCALE,
        SCREEN_HEIGHT * SCREEN_SCALE,
        SDL_WINDOW_SHOWN
    );

    if (video.window == NULL) {
        printf("Window could not be created!: %s", SDL_GetError());
        exit(-1);
    }

    video.surface = SDL_GetWindowSurface(video.window);
    SDL_FillRect(video.surface, NULL, SDL_MapRGB(video.surface->format, 0x00, 0x00, 0x00));
    SDL_UpdateWindowSurface(video.window);
    
    return video;
}
