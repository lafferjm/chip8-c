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

void add_registers(CPU*, uint8_t, uint8_t);
void subtract_registers(CPU*, uint8_t, uint8_t, uint8_t);
void shift_left(CPU*, uint8_t);
void shift_right(CPU*, uint8_t);

void load_memory(CPU*, uint8_t);
void store_memory(CPU*, uint8_t);

void call_subroutine(CPU*, uint16_t);
void return_from_subroutine(CPU*, uint16_t);

void decimal_encoded_conversion(CPU*, uint8_t);

void add_to_index(CPU*, uint8_t);

void jump_with_offset(CPU*, uint16_t);

void generate_random(CPU*, uint16_t);

#endif