#ifndef MAGIC6502_H
#define MAGIC6502_H

#include "magic6502_structs.h"

magic6502_ctx* magic6502_init(void* app_ctx, unsigned char* (*ma)(void*, unsigned short));
void magic6502_interrupt(magic6502_ctx* ctx, char type);
unsigned char magic6502_exec(magic6502_ctx* ctx);
void magic6502_free(magic6502_ctx* ctx);

#endif
