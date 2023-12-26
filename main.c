#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "chip8.h"
#include "cpu.h"

int main(int argc, char** argv) {
    CPU cpu;
    load_font(&cpu);
    load_rom("roms/ibm_logo.ch8", &cpu);

    cpu.pc = 0x200;

    
}
