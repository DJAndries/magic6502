#include "instructions.h"
#include "instr_helpers.h"
#include "interrupts.h"

void adc(magic6502_ctx* ctx, unsigned char val) {
  unsigned short result = ctx->a + val + ctx->c;
  zero_calc(ctx, result);
  carry_calc(ctx, result);
  overflow_calc(ctx, val, result);
  negative_calc(ctx, result);
  set_acc(ctx, result);
}

void and(magic6502_ctx* ctx, unsigned char val) {
  ctx->a = ctx->a & val;
  negative_calc(ctx, ctx->a);
  zero_calc(ctx, ctx->a);
}

void asl(magic6502_ctx* ctx, unsigned short addr, char a) {
  unsigned short result = (a == 1 ? ctx->a : (*ctx->memory)[addr]) << 1;
  carry_calc(ctx, result);
  zero_calc(ctx, result);
  negative_calc(ctx, result);
  if (a == 1) {
    set_acc(ctx, result);
  } else {
    (*ctx->memory)[addr] = result & 0xFF;
  }
}

void bcc(magic6502_ctx* ctx, unsigned short addr) {
  if (ctx->c == 0) {
    ctx->pc = addr;
  }
}

void bcs(magic6502_ctx* ctx, unsigned short addr) {
  if (ctx->c == 1) {
    ctx->pc = addr;
  }
}

void beq(magic6502_ctx* ctx, unsigned short addr) {
  if (ctx->z == 1) {
    ctx->pc = addr;
  }
}

void bit(magic6502_ctx* ctx, unsigned char val) {
  ctx->z = (ctx->a & val) == 0;
  ctx->n = val >> 7;
  ctx->v = (val >> 6) && 0x01;
}

void bmi(magic6502_ctx* ctx, unsigned short addr) {
  if (ctx->n == 1) {
    ctx->pc = addr;
  }
}

void bne(magic6502_ctx* ctx, unsigned short addr) {
  if (ctx->z == 0) {
    ctx->pc = addr;
  }
}

void bpl(magic6502_ctx* ctx, unsigned short addr) {
  if (ctx->n == 0) {
    ctx->pc = addr;
  }
}

void brk(magic6502_ctx* ctx) {
  execute_interrupt(ctx, MAGIC6502_INT_BRK);
}

void bvc(magic6502_ctx* ctx, unsigned short addr) {
  if (ctx->v == 0) {
    ctx->pc = addr;
  }
}

void bvs(magic6502_ctx* ctx, unsigned short addr) {
  if (ctx->v == 1) {
    ctx->pc = addr;
  }
}

void clc(magic6502_ctx* ctx) {
  ctx->c = 0;
}

void cld(magic6502_ctx* ctx) {
  ctx->d = 0;
}

void cli(magic6502_ctx* ctx) {
  ctx->i = 0;
}

void clv(magic6502_ctx* ctx) {
  ctx->v = 0;
}

void cmp(magic6502_ctx* ctx, unsigned char val) {
  unsigned short result = ctx->a - val;
  negative_calc(ctx, result);
  zero_calc(ctx, result);
  ctx->c = ctx->a >= val;
}

void cpx(magic6502_ctx* ctx, unsigned char val) {
  unsigned short result = ctx->x - val;
  negative_calc(ctx, result);
  zero_calc(ctx, result);
  ctx->c = ctx->x >= val;
}

void cpy(magic6502_ctx* ctx, unsigned char val) {
  unsigned short result = ctx->y - val;
  negative_calc(ctx, result);
  zero_calc(ctx, result);
  ctx->c = ctx->y >= val;
}

void dec(magic6502_ctx* ctx, unsigned short addr) {
  (*ctx->memory)[addr] = (*ctx->memory)[addr] - 1;
  zero_calc(ctx, (*ctx->memory)[addr]);
  negative_calc(ctx, (*ctx->memory)[addr]);
}

void dex(magic6502_ctx* ctx) {
  ctx->x = ctx->x - 1;
  zero_calc(ctx, ctx->x);
  negative_calc(ctx, ctx->x);
}

void dey(magic6502_ctx* ctx) {
  ctx->y = ctx->y - 1;
  zero_calc(ctx, ctx->y);
  negative_calc(ctx, ctx->y);
}

void eor(magic6502_ctx* ctx, unsigned char val) {
  ctx->a = ctx->a ^ val;
  zero_calc(ctx, ctx->a);
  negative_calc(ctx, ctx->a);
}

void inc(magic6502_ctx* ctx, unsigned short addr) {
  (*ctx->memory)[addr] = (*ctx->memory)[addr] + 1;
  zero_calc(ctx, (*ctx->memory)[addr]);
  negative_calc(ctx, (*ctx->memory)[addr]);
}

void inx(magic6502_ctx* ctx) {
  ctx->x = ctx->x + 1;
  zero_calc(ctx, ctx->x);
  negative_calc(ctx, ctx->x);
}

void iny(magic6502_ctx* ctx) {
  ctx->y = ctx->y + 1;
  zero_calc(ctx, ctx->y);
  negative_calc(ctx, ctx->y);
}

void jmp(magic6502_ctx* ctx, unsigned short addr) {
  ctx->pc = addr;
}

void jsr(magic6502_ctx* ctx, unsigned short addr) {
  push_short_to_stack(ctx, ctx->pc + 3);
  ctx->pc = addr;
}

void lda(magic6502_ctx* ctx, unsigned char val) {
  ctx->a = val;
  zero_calc(ctx, ctx->a);
  negative_calc(ctx, ctx->a);
}

void ldx(magic6502_ctx* ctx, unsigned char val) {
  ctx->x = val;
  zero_calc(ctx, ctx->x);
  negative_calc(ctx, ctx->x);
}

void ldy(magic6502_ctx* ctx, unsigned char val) {
  ctx->y = val;
  zero_calc(ctx, ctx->y);
  negative_calc(ctx, ctx->y);
}

void lsr(magic6502_ctx* ctx, unsigned short addr, char a) {
  unsigned char value = a == 1 ? a : (*ctx->memory)[addr];
  ctx->c = value & 0x01;
  value = value >> 1;
  if (a == 1) {
    ctx->a = value;
  } else {
    (*ctx->memory)[addr] = value;
  }
  zero_calc(ctx, value);
  negative_calc(ctx, value);
}

void ora(magic6502_ctx* ctx, unsigned char val) {
  ctx->a = ctx->a | val;
  zero_calc(ctx, ctx->a);
  negative_calc(ctx, ctx->a);
}

void pha(magic6502_ctx* ctx) {
  push_to_stack(ctx, ctx->a);
}

void php(magic6502_ctx* ctx) {
  push_to_stack(ctx, serialize_status(ctx, 1));
}

void pla(magic6502_ctx* ctx) {
  ctx->a = pull_from_stack(ctx);
  zero_calc(ctx, ctx->a);
  negative_calc(ctx, ctx->a);
}

void plp(magic6502_ctx* ctx) {
  load_status(ctx, pull_from_stack(ctx));
}

void rol(magic6502_ctx* ctx, unsigned short addr, char a) {
  unsigned char value = a == 1 ? a : (*ctx->memory)[addr];
  unsigned char result = (value << 1) | ctx->c;
  ctx->c = (value & 0x80) >> 7;
  if (a == 1) {
    ctx->a = result;
  } else {
    (*ctx->memory)[addr] = result;
  }
  zero_calc(ctx, result);
  negative_calc(ctx, result);
}

void ror(magic6502_ctx* ctx, unsigned short addr, char a) {
  unsigned char value = a == 1 ? a : (*ctx->memory)[addr];
  unsigned char result = (value >> 1) | (ctx->c << 7);
  ctx->c = value & 0x01;
  if (a == 1) {
    ctx->a = result;
  } else {
    (*ctx->memory)[addr] = result;
  }
  zero_calc(ctx, result);
  negative_calc(ctx, result);
}

void rti(magic6502_ctx* ctx) {
  load_status(ctx, pull_from_stack(ctx));
  ctx->pc = pull_short_from_stack(ctx);
}

void rts(magic6502_ctx* ctx) {
  ctx->pc = pull_short_from_stack(ctx);
}

void sbc(magic6502_ctx* ctx, unsigned char val) {
  unsigned short result = ctx->a - val - (1 - ctx->c);
  carry_calc(ctx, result);
  zero_calc(ctx, result);
  overflow_calc(ctx, val, result);
  negative_calc(ctx, result);
  ctx->a = result;
}

void sec(magic6502_ctx* ctx) {
  ctx->c = 1;
}

void sed(magic6502_ctx* ctx) {
  ctx->d = 1;
}

void sei(magic6502_ctx* ctx) {
  ctx->i = 1;
}

void sta(magic6502_ctx* ctx, unsigned short addr) {
  (*ctx->memory)[addr] = ctx->a;
}

void stx(magic6502_ctx* ctx, unsigned short addr) {
  (*ctx->memory)[addr] = ctx->x;
}

void sty(magic6502_ctx* ctx, unsigned short addr) {
  (*ctx->memory)[addr] = ctx->y;
}

void tax(magic6502_ctx* ctx) {
  ctx->x = ctx->a;
  zero_calc(ctx, ctx->x);
  negative_calc(ctx, ctx->x);
}

void tay(magic6502_ctx* ctx) {
  ctx->y = ctx->a;
  zero_calc(ctx, ctx->y);
  negative_calc(ctx, ctx->y);
}

void tsx(magic6502_ctx* ctx) {
  ctx->x = ctx->sp;
  zero_calc(ctx, ctx->x);
  negative_calc(ctx, ctx->x);
}

void txa(magic6502_ctx* ctx) {
  ctx->a = ctx->x;
  zero_calc(ctx, ctx->a);
  negative_calc(ctx, ctx->a);
}

void txs(magic6502_ctx* ctx) {
  ctx->sp = ctx->x;
}

void tya(magic6502_ctx* ctx) {
  ctx->a = ctx->y;
  zero_calc(ctx, ctx->a);
  negative_calc(ctx, ctx->a);
}
