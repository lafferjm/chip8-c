#ifndef __CHIP8_VIDEO_H__
#define __CHIP8_VIDEO_H__

#include <SDL2/SDL.h>

typedef struct video {
    SDL_Window* window;
    SDL_Surface* surface;
    SDL_Renderer* renderer;
} Video;

Video init_video();
void update_display(Video*, uint32_t*);

#endif
