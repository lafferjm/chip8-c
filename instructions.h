#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__

#include "video.h"
#include "cpu.h"

void clear_screen(Video*);
void jump(CPU*, uint16_t);
void set_register(CPU*, uint16_t);
void add_to_register(CPU*, uint16_t);
void set_index_register(CPU*, uint16_t);
void display(CPU*, uint16_t);

#endif