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

void skip_if_equal_value(CPU*, uint16_t);
void skip_if_not_equal_value(CPU*, uint16_t);
void skip_if_equal_registers(CPU*, uint16_t);
void skip_if_not_equal_registers(CPU*, uint16_t);

void set_register_x_y(CPU*, uint8_t, uint8_t);
void or_register(CPU*, uint8_t, uint8_t);
void and_register(CPU*, uint8_t, uint8_t);
void xor_register(CPU*, uint8_t, uint8_t);

#endif