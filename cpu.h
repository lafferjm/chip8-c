#ifndef __CPU_H__
#define __CPU_H__

#include <stdint.h>

typedef struct cpu {
    uint8_t memory[4096];
    uint8_t registers[16];
    uint32_t display[64*32];
    uint16_t pc;
    uint16_t index;
    uint16_t stack[16];
    uint8_t sp;
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint8_t keypad[16];
} CPU;

uint16_t fetch_opcode(CPU*);
void init_cpu(CPU*);

#endif
