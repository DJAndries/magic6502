#include "interrupts.h"
#include "instr_helpers.h"
#include <string.h>

void reset_registers(magic6502_ctx* ctx) {
  unsigned char* (*ma)(void*, unsigned short) = ctx->ma;
  unsigned char* m = ctx->m;
  memset(ctx, 0, sizeof(magic6502_ctx));
  ctx->m = m;
  ctx->ma = ma;
}

void execute_interrupt(magic6502_ctx* ctx, char type) {
  unsigned short addr_vector;
  unsigned short saved_pc;
  switch (type) {
    case MAGIC6502_INT_BRK:
      addr_vector = 0xFFFE;
      break;
    case MAGIC6502_INT_NMI:
      addr_vector = 0xFFFA;
      break;
    case MAGIC6502_INT_RESET:
      reset_registers(ctx);
      addr_vector = 0xFFFC;
      break;
    case MAGIC6502_INT_IRQ:
    default:
      if (ctx->i == 1) {
        return;
      }
      addr_vector = 0xFFFE;
      break;
  }
  if (type == MAGIC6502_INT_BRK) {
    ctx->b = 1;
  } else {
    ctx->b = 0;
  }
  if (type != MAGIC6502_INT_RESET) {
    saved_pc = type == MAGIC6502_INT_BRK ? (ctx->pc + 2) : ctx->pc;
    push_short_to_stack(ctx, saved_pc);
    push_to_stack(ctx, serialize_status(ctx, ctx->b));
  }
  ctx->i = 1;
  ctx->pc = *ctx->ma(ctx, addr_vector) | (*ctx->ma(ctx, addr_vector + 1) << 8);
}
