#include <stdio.h>
#include <stdlib.h>
#include "magic6502.h"

#define CALL_TRACE_ENABLED 1
#define CALL_TRACE_INST_COUNT_START 26764800

typedef struct {
  unsigned char* memory;
} test_ctx;

void read_program(char* filename, void* ctx) {
  FILE* fp;
  fp = fopen(filename, "rb");
  fread(((test_ctx*)ctx)->memory + 0x400, sizeof(unsigned char), 0xFFFF - 0x400, fp);
  fclose(fp);
}

unsigned char* memory_access(void* ctx, unsigned short addr) {
  return &((test_ctx*)ctx)->memory[addr];
}

void call_trace(magic6502_ctx* magic_ctx, unsigned char* memory, unsigned long inst_count) {
  if (CALL_TRACE_ENABLED && inst_count >= CALL_TRACE_INST_COUNT_START) {
    printf("A: %x\nY: %x\nX: %x\n", magic_ctx->a, magic_ctx->y, magic_ctx->x);
    printf("C=%x Z=%x n=%x v=%x\n\
Stack top: %x %x\n\
%x %x\n\n",
      magic_ctx->c, magic_ctx->z, magic_ctx->n, magic_ctx->v,
      magic_ctx->sp, memory[0x100 | (magic_ctx->sp + 1)], magic_ctx->pc, memory[magic_ctx->pc]);
  }
}

char run_test(test_ctx* ctx) {
  unsigned long inst_count = 0;
  magic6502_ctx* magic_ctx = magic6502_init(ctx, memory_access);

  read_program("functional_test.bin", ctx);
  magic_ctx->pc = 0x400;

  while (magic_ctx->pc != 1 && magic_ctx->pc != 2) {
    call_trace(magic_ctx, ctx->memory, inst_count);
    magic6502_exec(magic_ctx);
    inst_count = inst_count + 1;
  }

  if (magic_ctx->pc == 1) {
    printf("Fail\n");
  } else {
    printf("Pass!!\n");
  }

  printf("Instructions executed: %lu\n", inst_count);

  magic6502_free(magic_ctx);

  return magic_ctx->pc == 1;
}

int main(int argc, char** argv) {
  test_ctx* ctx = (test_ctx*)malloc(sizeof(test_ctx));
  ctx->memory = (unsigned char*)malloc(sizeof(unsigned char*) * 65536);

  run_test(ctx);

  free(ctx->memory);
  free(ctx);
  return 0;
}
