#ifndef __CHIP8_H__
#define __CHIP8_H__

#include "cpu.h"

void load_font(CPU*);
void load_rom(char*, CPU*);

#endif