#ifndef ADDRESSING_H
#define ADDRESSING_H

#include "magic6502_structs.h"

unsigned char fetch_char(magic6502_ctx* ctx, unsigned short addr);
unsigned short fetch_short(magic6502_ctx* ctx, unsigned short addr);

unsigned short indexed_indirect_addr(magic6502_ctx* ctx);
unsigned short indirect_indexed_addr(magic6502_ctx* ctx);
unsigned char zero_page_addr(magic6502_ctx* ctx);
unsigned char zero_page_x_addr(magic6502_ctx* ctx);
unsigned char zero_page_y_addr(magic6502_ctx* ctx);
unsigned char immediate(magic6502_ctx* ctx);
unsigned short absolute_addr(magic6502_ctx* ctx);
unsigned short absolute_x_addr(magic6502_ctx* ctx);
unsigned short absolute_y_addr(magic6502_ctx* ctx);
unsigned short relative_addr(magic6502_ctx* ctx);
unsigned short indirect_addr(magic6502_ctx* ctx);

#endif
