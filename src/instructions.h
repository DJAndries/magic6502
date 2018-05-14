#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "magic6502_structs.h"

void adc(magic6502_ctx* ctx, unsigned char val);
void and(magic6502_ctx* ctx, unsigned char val);
void asl(magic6502_ctx* ctx, unsigned short addr, char a);
char bcc(magic6502_ctx* ctx, unsigned short addr);
char bcs(magic6502_ctx* ctx, unsigned short addr);
char beq(magic6502_ctx* ctx, unsigned short addr);
void bit(magic6502_ctx* ctx, unsigned char val);
char bmi(magic6502_ctx* ctx, unsigned short addr);
char bne(magic6502_ctx* ctx, unsigned short addr);
char bpl(magic6502_ctx* ctx, unsigned short addr);
void brk(magic6502_ctx* ctx);
char bvc(magic6502_ctx* ctx, unsigned short addr);
char bvs(magic6502_ctx* ctx, unsigned short addr);
void clc(magic6502_ctx* ctx);
void cld(magic6502_ctx* ctx);
void cli(magic6502_ctx* ctx);
void clv(magic6502_ctx* ctx);
void cmp(magic6502_ctx* ctx, unsigned char val);
void cpx(magic6502_ctx* ctx, unsigned char val);
void cpy(magic6502_ctx* ctx, unsigned char val);
void dec(magic6502_ctx* ctx, unsigned short addr);
void dex(magic6502_ctx* ctx);
void dey(magic6502_ctx* ctx);
void eor(magic6502_ctx* ctx, unsigned char val);
void inc(magic6502_ctx* ctx, unsigned short addr);
void inx(magic6502_ctx* ctx);
void iny(magic6502_ctx* ctx);
void jmp(magic6502_ctx* ctx, unsigned short addr);
void jsr(magic6502_ctx* ctx, unsigned short addr);
void lda(magic6502_ctx* ctx, unsigned char val);
void ldx(magic6502_ctx* ctx, unsigned char val);
void ldy(magic6502_ctx* ctx, unsigned char val);
void lsr(magic6502_ctx* ctx, unsigned short addr, char a);
void ora(magic6502_ctx* ctx, unsigned char val);
void pha(magic6502_ctx* ctx);
void php(magic6502_ctx* ctx);
void pla(magic6502_ctx* ctx);
void plp(magic6502_ctx* ctx);
void rol(magic6502_ctx* ctx, unsigned short addr, char a);
void ror(magic6502_ctx* ctx, unsigned short addr, char a);
void rti(magic6502_ctx* ctx);
void rts(magic6502_ctx* ctx);
void sbc(magic6502_ctx* ctx, unsigned char val);
void sec(magic6502_ctx* ctx);
void sed(magic6502_ctx* ctx);
void sei(magic6502_ctx* ctx);
void sta(magic6502_ctx* ctx, unsigned short addr);
void stx(magic6502_ctx* ctx, unsigned short addr);
void sty(magic6502_ctx* ctx, unsigned short addr);
void tax(magic6502_ctx* ctx);
void tay(magic6502_ctx* ctx);
void tsx(magic6502_ctx* ctx);
void txa(magic6502_ctx* ctx);
void txs(magic6502_ctx* ctx);
void tya(magic6502_ctx* ctx);

#endif
