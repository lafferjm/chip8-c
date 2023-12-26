#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "chip8.h"
#include "cpu.h"
#include "video.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Incorrect usage: chip8 <ROM>\n");
        exit(-1);
    }

    Video video = init_video();
    
    CPU cpu;
    cpu.pc = 0x200;

    load_font(&cpu);
    load_rom(argv[1], &cpu);

    SDL_Event e;
    bool running = false;
    uint16_t opcode;

    while(running == false) { 
        opcode = fetch_opcode(&cpu);
        cpu.pc += 2;
    
        if (opcode == 0x00E0) {
            clear_screen(&video);
        }

        printf("0x%04x\n", opcode);
    
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = true;
            }
        }
    }

    SDL_DestroyWindow(video.window);
    SDL_Quit();
    
    return 0;
}
