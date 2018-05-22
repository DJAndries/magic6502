#include "magic6502.h"
#include "interrupts.h"
#include "execute.h"
#include <stdlib.h>
#include <string.h>

__attribute__((visibility("default"))) \
magic6502_ctx* magic6502_init(void* app_ctx, unsigned char* (*ma)(void*, unsigned short)) {
  magic6502_ctx* ctx = (magic6502_ctx*)malloc(sizeof(magic6502_ctx));
  if (ctx == 0) {
    return 0;
  }

  memset(ctx, 0, sizeof(magic6502_ctx));

  ctx->app_ctx = app_ctx;
  ctx->ma = ma;

  return ctx;
}

__attribute__((visibility("default"))) void magic6502_interrupt(magic6502_ctx* ctx, char type) {
  execute_interrupt(ctx, type);
}

__attribute__((visibility("default"))) unsigned char magic6502_exec(magic6502_ctx* ctx) {
  return execute(ctx);
}

__attribute__((visibility("default"))) void magic6502_free(magic6502_ctx* ctx) {
  free(ctx);
}
