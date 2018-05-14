#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "magic6502_structs.h"

void execute_interrupt(magic6502_ctx* ctx, char type);

#endif
