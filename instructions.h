#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__

#include "cpu.h"

void jump(CPU*, uint16_t);
void set_register(CPU*, uint16_t);
void add_to_register(CPU*, uint16_t);
void set_index_register(CPU*, uint16_t);

#endif