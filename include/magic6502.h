#ifndef MAGIC6502_H
#define MAGIC6502_H

#include "magic6502_structs.h"

magic6502_ctx* magic6502_init(char** memory);
void magic6502_interrupt(magic6502_ctx* ctx, char type);
void magic6502_exec(magic6502_ctx* ctx);

#endif
