#include "cpu.h"
#include "string.h"

uint16_t fetch_opcode(CPU* cpu) {
    uint16_t opcode = (cpu->memory[cpu->pc] << 8) | cpu->memory[cpu->pc + 1];

    return opcode;
}

void init_cpu(CPU* cpu) {
    memset(cpu->memory, 0, sizeof(cpu->memory));
    memset(cpu->registers, 0, sizeof(cpu->registers));
    memset(cpu->display, 0, sizeof(cpu->display));
    memset(cpu->stack, 0, sizeof(cpu->stack));
    memset(cpu->keypad, 0, sizeof(cpu->keypad));

    cpu->sp = 0;
    cpu->pc = 0x200;
}