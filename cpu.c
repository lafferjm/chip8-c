#include "cpu.h"

uint16_t fetch_opcode(CPU* cpu) {
    uint16_t opcode = (cpu->memory[cpu->pc] << 8) | cpu->memory[cpu->pc + 1];

    return opcode;
}