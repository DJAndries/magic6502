#include "interrupts.h"
#include "instr_helpers.h"
#include <string.h>

void reset_registers(magic6502_ctx* ctx) {
  unsigned char** memory = ctx->memory;
  memset(ctx, 0, sizeof(magic6502_ctx));
  ctx->sp = 0xFF;
  ctx->memory = memory;
}

void execute_interrupt(magic6502_ctx* ctx, char type) {
  short addr_vector;
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
  if (type != MAGIC6502_INT_RESET) {
    push_short_to_stack(ctx, ctx->pc + 1);
    push_to_stack(ctx, serialize_status(ctx));
  }
  ctx->i = 1;
  ctx->pc = (*ctx->memory)[addr_vector] & ((*ctx->memory)[addr_vector + 1] << 8);
  if (type == MAGIC6502_INT_BRK) {
    ctx->b = 1;
  }
}
