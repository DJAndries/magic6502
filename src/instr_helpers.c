#include "instr_helpers.h"

void overflow_calc(magic6502_ctx* ctx, unsigned char b, unsigned short c) {
  /* First part of test: a and b must have same sign */
  /* Second part of test: a and c must have different signs */
  ctx->v = (((ctx->a ^ c) & (b ^ c) & 0x80) >> 7) & 0x01;
}

void zero_calc(magic6502_ctx* ctx, unsigned short result) {
  ctx->z = (result & 0xFF) == 0;
}

void carry_calc(magic6502_ctx* ctx, unsigned short result) {
  ctx->c = (result & 0x100) >> 8;
}

void negative_calc(magic6502_ctx* ctx, unsigned short result) {
  ctx->n = (result & 0x80) >> 7;
}

void set_acc(magic6502_ctx* ctx, unsigned short result) {
  ctx->a = result & 0xFF;
}

void push_to_stack(magic6502_ctx* ctx, unsigned char value) {
  *ctx->ma(ctx->app_ctx, 0x0100 | ctx->sp) = value;
  ctx->sp = ctx->sp - 1;
}

void push_short_to_stack(magic6502_ctx* ctx, unsigned short value) {
  *ctx->ma(ctx->app_ctx, 0x0100 | ctx->sp) = (value & 0xFF00) >> 8;
  *ctx->ma(ctx->app_ctx, 0x0100 | (ctx->sp - 1 & 0xFF)) = value & 0xFF;
  ctx->sp = ctx->sp - 2;
}

unsigned char pull_from_stack(magic6502_ctx* ctx) {
  unsigned char value = *ctx->ma(ctx->app_ctx, 0x0100 | (ctx->sp + 1 & 0xFF));
  ctx->sp = ctx->sp + 1;
  return value;
}

unsigned short pull_short_from_stack(magic6502_ctx* ctx) {
  unsigned short value = *ctx->ma(ctx->app_ctx, 0x0100 | (ctx->sp + 1 & 0xFF)) |
    (*ctx->ma(ctx->app_ctx, 0x0100 | (ctx->sp + 2 & 0xFF)) << 8);
  ctx->sp = ctx->sp + 2;
  return value;
}

unsigned char serialize_status(magic6502_ctx* ctx, unsigned char b) {
  return ctx->c | (ctx->z << 1) | (ctx->i << 2) | (ctx->d << 3) \
    | (b << 4) | (0x01 << 5) | (ctx->v << 6) | (ctx->n << 7);
}

void load_status(magic6502_ctx* ctx, unsigned char status) {
  ctx->c = status & 0x01;
  ctx->z = (status >> 1) & 0x01;
  ctx->i = (status >> 2) & 0x01;
  ctx->d = (status >> 3) & 0x01;
  ctx->b = (status >> 4) & 0x01;
  ctx->v = (status >> 6) & 0x01;
  ctx->n = (status >> 7) & 0x01;
}
