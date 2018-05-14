#include <stdio.h>
#include <stdlib.h>
#include "magic6502.h"

int main(int argc, char** argv) {
  unsigned char* memory = (unsigned char*)malloc(sizeof(unsigned char*) * 65536);
  magic6502_ctx* magic_ctx = magic6502_init(&memory);



  return 0;
}
