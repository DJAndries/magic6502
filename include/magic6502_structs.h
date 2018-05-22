#ifndef MAGIC6502_STRUCTS_H
#define MAGIC6502_STRUCTS_H

#define MAGIC6502_INT_BRK 1
#define MAGIC6502_INT_IRQ 2
#define MAGIC6502_INT_NMI 3
#define MAGIC6502_INT_RESET 4

typedef struct {
  unsigned short pc;
  unsigned char sp;
  unsigned char a;
  unsigned char x;
  unsigned char y;

  unsigned char c;
  unsigned char z;
  unsigned char i;
  unsigned char d;
  unsigned char b;
  unsigned char v;
  unsigned char n;

  void* app_ctx;
  unsigned char* (*ma)(void*, unsigned short);
  unsigned short address_accessed;
} magic6502_ctx;

#endif
