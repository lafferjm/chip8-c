#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "chip8.h"
#include "cpu.h"
#include "instructions.h"
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
    
        switch (opcode & 0xF000) {
            case 0x0000:
                clear_screen(&video);
                break;
            case 0x1000:
                jump(&cpu, opcode);
                break;
            case 0x6000:
                set_register(&cpu, opcode);
                break;
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
