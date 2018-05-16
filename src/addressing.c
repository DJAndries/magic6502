#include "addressing.h"

unsigned char fetch_char(magic6502_ctx* ctx, unsigned short addr) {
  return (*ctx->memory)[addr];
}

unsigned short fetch_short(magic6502_ctx* ctx, unsigned short addr) {
  return (*ctx->memory)[addr] | ((*ctx->memory)[addr + 1] << 8);
}

unsigned short indexed_indirect_addr(magic6502_ctx* ctx) {
  unsigned char addr = (*ctx->memory)[ctx->pc + 1] + ctx->x;
  return fetch_short(ctx, addr);
}

unsigned short indirect_indexed_addr(magic6502_ctx* ctx) {
  return fetch_short(ctx, (*ctx->memory)[ctx->pc + 1]) + ctx->y;
}

unsigned char zero_page_addr(magic6502_ctx* ctx) {
  return (*ctx->memory)[ctx->pc + 1];
}

unsigned char zero_page_x_addr(magic6502_ctx* ctx) {
  return (*ctx->memory)[ctx->pc + 1] + ctx->x;
}

unsigned char zero_page_y_addr(magic6502_ctx* ctx) {
  return (*ctx->memory)[ctx->pc + 1] + ctx->y;
}

unsigned char immediate(magic6502_ctx* ctx) {
  return (*ctx->memory)[ctx->pc + 1];
}

unsigned short absolute_addr(magic6502_ctx* ctx) {
  return (*ctx->memory)[ctx->pc + 1] | ((*ctx->memory)[ctx->pc + 2] << 8);
}

unsigned short absolute_x_addr(magic6502_ctx* ctx) {
  return absolute_addr(ctx) + ctx->x;
}

unsigned short absolute_y_addr(magic6502_ctx* ctx) {
  return absolute_addr(ctx) + ctx->y;
}

unsigned short relative_addr(magic6502_ctx* ctx) {
  return ctx->pc + (char)(*ctx->memory)[ctx->pc + 1];
}

unsigned short indirect_addr(magic6502_ctx* ctx) {
  return fetch_short(ctx, absolute_addr(ctx));
}
