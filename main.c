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
    init_cpu(&cpu);

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
            case 0x3000:
                skip_if_equal_value(&cpu, opcode);
                break;
            case 0x4000:
                skip_if_not_equal_value(&cpu, opcode);
                break;
            case 0x5000:
                skip_if_equal_registers(&cpu, opcode);
                break;
            case 0x6000:
                set_register(&cpu, opcode);
                break;
            case 0x7000:
                add_to_register(&cpu, opcode);
                break;
            case 0x8000: {
                uint8_t vx = (opcode & 0x0F00) >> 8;
                uint8_t vy = (opcode & 0x00F0) >> 4;

                switch (opcode & 0x000F) {
                    case 0x0:
                        set_register_x_y(&cpu, vx, vy);
                        break;
                    case 0x1:
                        or_register(&cpu, vx, vy);
                        break;
                    case 0x2:
                        and_register(&cpu, vx, vy);
                        break;
                    case 0x3:
                        xor_register(&cpu, vx, vy);
                        break;
                }
                break;
            }
            case 0x9000:
                skip_if_not_equal_registers(&cpu, opcode);
                break;
            case 0xA000:
                set_index_register(&cpu, opcode);
                break;
            case 0xD000:
                display(&cpu, opcode);
                update_display(&video, cpu.display);
                break;
        }

        // printf("0x%04x\n", opcode);
    
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = true;
            }
        }

        SDL_Delay(1000/60);
    }

    SDL_DestroyWindow(video.window);
    SDL_Quit();
    
    return 0;
}
