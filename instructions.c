#include "cpu.h"
#include "instructions.h"
#include "video.h"

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

void clear_screen(Video* video) {
    SDL_FillRect(video->surface, NULL, SDL_MapRGB(video->surface->format, 0x00, 0x00, 0x00));
    SDL_UpdateWindowSurface(video->window);
}
