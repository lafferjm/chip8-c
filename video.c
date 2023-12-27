#include <SDL2/SDL.h>
#include "video.h"

const int SCREEN_WIDTH = 64;
const int SCREEN_HEIGHT = 32;
const int SCREEN_SCALE = 16;

Video init_video() {
    Video video;
    video.window = NULL;
    video.surface =  NULL;
    video.renderer = NULL;

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
    
    video.renderer = SDL_CreateRenderer(video.window, -1, SDL_RENDERER_ACCELERATED);

    if(video.renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        exit(-1);
    }

    SDL_SetRenderDrawColor(video.renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(video.renderer);

    return video;
}

void update_display(Video* video, uint32_t* display) {
    SDL_Rect rect;

    SDL_SetRenderDrawColor(video->renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(video->renderer);

    for (unsigned int x = 0; x < 64; x++) {
        for (unsigned int y = 0; y < 32; y++) {
            if (display[x + y * 64]) {
                rect.x = x * 16;
                rect.y = y * 16;
                rect.w = 16;
                rect.h = 16;
            }

            SDL_SetRenderDrawColor(video->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderFillRect(video->renderer, &rect);
        }
    }

    SDL_RenderPresent(video->renderer);
}
