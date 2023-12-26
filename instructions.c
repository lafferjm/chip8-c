#include "cpu.h"
#include "instructions.h"
#include "video.h"

void clear_screen(Video* video) {
    SDL_SetRenderDrawColor(video->renderer, 00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(video->renderer);
}

void jump(CPU* cpu, uint16_t opcode) {
    uint16_t address = opcode & 0x0FFFu;
    cpu->pc = address;
}

void set_register(CPU* cpu, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8;
    uint8_t value = opcode & 0x00FFu;

    cpu->registers[vx] = value;
}

void add_to_register(CPU* cpu, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8;
    uint8_t value = opcode & 0x00FFu;

    cpu->registers[vx] = cpu->registers[vx] + value;
}

void set_index_register(CPU* cpu, uint16_t opcode) {
    uint16_t value = opcode & 0x0FFFu;
    cpu->index = value;
}

void display(CPU* cpu, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8;
    uint8_t vy = (opcode & 0x00F0u) >> 4;
    uint8_t height = opcode & 0x000Fu;

    uint8_t x = cpu->registers[vx] % 64;
    uint8_t y = cpu->registers[vy] % 32;

    cpu->registers[0xF] = 0;
    for (unsigned int row = 0; row < height; row++) {
        uint8_t sprite_data = cpu->memory[row + cpu->index];
        
        for (unsigned int column = 0; column < 8; column++) {
            uint8_t sprite_pixel = sprite_data & (0x80u >> column);
            uint32_t screen_pixel = cpu->display[(y + row) * 64 + (x + column)];

            if (sprite_pixel) {
                if (screen_pixel == 0xFFFFFFFF) {
                    cpu->registers[0xF] = 1;
                }

                screen_pixel = screen_pixel ^ 0xFFFFFFFF;
                cpu->display[(y + row) * 64 + (x + column)] = screen_pixel;
            }
        }
    }
}
