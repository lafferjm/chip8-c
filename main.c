#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

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
    
}
