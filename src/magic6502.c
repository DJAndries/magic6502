#include "magic6502.h"
#include "interrupts.h"
#include "execute.h"

magic6502_ctx* magic6502_init(char** memory) {
  magic6502_ctx* ctx = malloc(sizeof(magic6502_ctx));
  memset(ctx, 0, sizeof(magic6502_ctx));

  ctx->sp = 0xFF;
  ctx->memory = memory;
}

void magic6502_interrupt(magic6502_ctx* ctx, char type) {
  execute_interrupt(ctx, type);
}

void magic6502_exec(magic6502_ctx* ctx) {
  execute(ctx);
}
