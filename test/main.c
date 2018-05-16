#include <stdio.h>
#include <stdlib.h>
#include "magic6502.h"

#define CALL_TRACE_ENABLED 0
#define CALL_TRACE_INST_COUNT_START 26764800

unsigned char* memory_access(void* magic_ctx, unsigned short addr) {
  return &((magic6502_ctx*)magic_ctx)->m[addr];
}

void read_program(unsigned char* memory) {
  FILE* fp;
  fp = fopen("test_prog.bin", "rb");
  printf("%d\n", fread(memory + 0x400, sizeof(unsigned char), 0xFFFF - 0x400, fp));
  fclose(fp);
}

int main(int argc, char** argv) {
  unsigned long inst_count = 0;
  unsigned char* memory = (unsigned char*)malloc(sizeof(unsigned char*) * 65536);
  magic6502_ctx* magic_ctx = magic6502_init(memory, memory_access);

  read_program(memory);
  magic_ctx->pc = 0x400;

  while (magic_ctx->pc != 1 && magic_ctx->pc != 2) {
    if (CALL_TRACE_ENABLED && inst_count > CALL_TRACE_INST_COUNT_START) {
      printf("A: %x\nY: %x\nX: %x\n", magic_ctx->a, magic_ctx->y, magic_ctx->x);
      if (memory[magic_ctx->pc] == 0) {
        printf("BREAK! %x %x\n", memory[0xFFFE], memory[0xFFFF]);
      }
      printf("C=%x Z=%x n=%x v=%x\n\
Stack top: %x %x\n\
%x %x\n\n",
        magic_ctx->c, magic_ctx->z, magic_ctx->n, magic_ctx->v,
        magic_ctx->sp, memory[0x100 | (magic_ctx->sp + 1)], magic_ctx->pc, memory[magic_ctx->pc]);
    }
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
  free(memory);

  return 0;
}
