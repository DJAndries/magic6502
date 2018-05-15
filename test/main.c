#include <stdio.h>
#include <stdlib.h>
#include "magic6502.h"

void read_program(unsigned char* memory) {
  FILE* fp;
  fp = fopen("test_prog.bin", "rb");
  printf("%d\n", fread(memory + 0x400, sizeof(unsigned char), 0xFFFF - 0x400, fp));
  fclose(fp);
}

int main(int argc, char** argv) {
  unsigned long inst_count = 0;
  unsigned char* memory = (unsigned char*)malloc(sizeof(unsigned char*) * 65536);
  magic6502_ctx* magic_ctx = magic6502_init(&memory);

  read_program(memory);
  magic_ctx->pc = 0x400;

  while (magic_ctx->pc != 1 && magic_ctx->pc != 2) {
    printf("A: %x\n", magic_ctx->a);
    printf("Y: %x\n", magic_ctx->y);
    printf("X: %x\n", magic_ctx->x);
    if (memory[magic_ctx->pc] == 0) {
      printf("BREAK!");
    }
    /* printf("C=%cu Z=%cu I=%cu D=%cu B=%cu v=%cu n=%cu", magic_ctx->c) */
    printf("Stack top: %x %x\n", magic_ctx->sp, memory[0x100 | (magic_ctx->sp + 1)]);
    printf("%x %x\n\n", magic_ctx->pc, memory[magic_ctx->pc]);
    magic6502_exec(magic_ctx);
    inst_count = inst_count + 1;
  }

  if (magic_ctx->pc == 1) {
    printf("Fail\n");
  }

  printf("Instructions executed: %lu\n", inst_count);

  magic6502_free(magic_ctx);
  free(memory);

  return 0;
}
