#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

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

    clock_t last_cycle_time;
    clock_t current_cycle_time;
    double delta_time;

    last_cycle_time = clock();

    while(running == false) {
        current_cycle_time = clock();
        delta_time = (current_cycle_time - last_cycle_time) / 1000;

        if (delta_time > 1) {
            last_cycle_time = current_cycle_time;

            opcode = fetch_opcode(&cpu);
            cpu.pc += 2;

            switch (opcode & 0xF000) {
                case 0x0000: {
                    switch (opcode & 0x00FF) {
                        case 0x00E0:
                            printf("CLEARING SCREEN\n");
                            clear_screen(&video);
                            break;
                        case 0x00EE:
                            return_from_subroutine(&cpu, opcode);
                            break;
                    }
                    break;
                }
                case 0x1000:
                    jump(&cpu, opcode);
                    break;
                case 0x2000:
                    call_subroutine(&cpu, opcode);
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
                        case 0x4:
                            add_registers(&cpu, vx, vy);
                            break;
                        case 0x5:
                            subtract_registers(&cpu, vx, vy, vx);
                            break;
                        case 0x6:
                            shift_right(&cpu, vx);
                            break;
                        case 0x7:
                            subtract_registers(&cpu, vy, vx, vx);
                            break;
                        case 0xE:
                            shift_left(&cpu, vx);
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
                case 0xF000: {
                    uint8_t x = (opcode & 0x0F00) >> 8;
                    switch (opcode & 0x00FF) {
                        case 0x0055:
                            store_memory(&cpu, x);
                            break;
                        case 0x0065:
                            load_memory(&cpu, x);
                            break;
                        case 0x0033:
                            decimal_encoded_conversion(&cpu, x);
                            break;
                    }
                    break;
                }
                default:
                    printf("UNKNOWN OPCODE: %04x\n", opcode);
                    break;
            }
        
            while(SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    running = true;
                }
            }
        }
    }

    SDL_DestroyRenderer(video.renderer);
    SDL_DestroyWindow(video.window);
    SDL_Quit();
    
    return 0;
}
