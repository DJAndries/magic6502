#ifndef INSTR_HELPERS_H
#define INSTR_HELPERS_H

#include "magic6502_structs.h"

void overflow_calc(magic6502_ctx* ctx, unsigned char b, unsigned short c);
void zero_calc(magic6502_ctx* ctx, unsigned short result);
void carry_calc(magic6502_ctx* ctx, unsigned short result);
void negative_calc(magic6502_ctx* ctx, unsigned short result);

void set_acc(magic6502_ctx* ctx, unsigned short result);

void push_to_stack(magic6502_ctx* ctx, unsigned char value);
void push_short_to_stack(magic6502_ctx* ctx, unsigned short value);
unsigned char pull_from_stack(magic6502_ctx* ctx);
unsigned short pull_short_from_stack(magic6502_ctx* ctx);

unsigned char serialize_status(magic6502_ctx* ctx);
void load_status(magic6502_ctx* ctx, unsigned char status);

#endif
