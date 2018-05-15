#include "magic6502.h"
#include "interrupts.h"
#include "execute.h"
#include <stdlib.h>
#include <string.h>

magic6502_ctx* __attribute__((visibility("default"))) magic6502_init(unsigned char** memory) {
  magic6502_ctx* ctx = (magic6502_ctx*)malloc(sizeof(magic6502_ctx));
  if (ctx == 0) {
    return 0;
  }

  memset(ctx, 0, sizeof(magic6502_ctx));

  ctx->memory = memory;

  return ctx;
}

void __attribute__((visibility("default"))) magic6502_interrupt(magic6502_ctx* ctx, char type) {
  execute_interrupt(ctx, type);
}

void __attribute__((visibility("default"))) magic6502_exec(magic6502_ctx* ctx) {
  execute(ctx);
}

void __attribute__((visibility("default"))) magic6502_free(magic6502_ctx* ctx) {
  free(ctx);
}
