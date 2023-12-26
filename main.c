#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "chip8.h"
#include "cpu.h"

int main(int argc, char** argv) {
    CPU cpu;
    cpu.pc = 0x200;

    load_font(&cpu);
    load_rom("roms/ibm_logo.ch8", &cpu);

    uint16_t opcode = (cpu.memory[cpu.pc] << 8) | cpu.memory[cpu.pc + 1];
    cpu.pc += 2;
    
    printf("0x%04x", opcode);
    
    SDL_Window* window = NULL;
    SDL_Surface* screen_surface = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(-1);
    }

    window = SDL_CreateWindow("CHIP8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 64 * 16, 32 * 16, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created!: %s\n", SDL_GetError());
        exit(-1);
    }

    screen_surface = SDL_GetWindowSurface(window);
    SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 0x00, 0x00, 0x00));

    SDL_UpdateWindowSurface(window);

    SDL_Event e;
    bool running = false;
    while(running == false) { 
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = true;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}
