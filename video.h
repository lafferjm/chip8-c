#ifndef __CHIP8_VIDEO_H__
#define __CHIP8_VIDEO_H__

#include <SDL2/SDL.h>

typedef struct video {
    SDL_Window* window;
    SDL_Surface* surface;
} Video;

Video init_video();

void clear_screen(Video*);

#endif
