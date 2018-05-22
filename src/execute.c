#include "instructions.h"
#include "addressing.h"
#include "cycle_count.h"

unsigned char execute(magic6502_ctx* ctx) {
  unsigned char inst = *ctx->ma(ctx->app_ctx, ctx->pc);
  unsigned char pc_inc = 2;
  switch (inst) {
    case 0x00:
      brk(ctx);
      pc_inc = 0;
      break;
    case 0x01:
      ora(ctx, fetch_char(ctx, indexed_indirect_addr(ctx)));
      break;
    case 0x05:
      ora(ctx, fetch_char(ctx, zero_page_addr(ctx)));
      break;
    case 0x06:
      asl(ctx, zero_page_addr(ctx), 0);
      break;
    case 0x08:
      php(ctx);
      pc_inc = 1;
      break;
    case 0x09:
      ora(ctx, immediate(ctx));
      break;
    case 0x0A:
      asl(ctx, 0, 1);
      pc_inc = 1;
      break;
    case 0x0D:
      ora(ctx, fetch_char(ctx, absolute_addr(ctx)));
      pc_inc = 3;
      break;
    case 0x0E:
      asl(ctx, absolute_addr(ctx), 0);
      pc_inc = 3;
      break;
    case 0x10:
      bpl(ctx, relative_addr(ctx));
      break;
    case 0x11:
      ora(ctx, fetch_char(ctx, indirect_indexed_addr(ctx)));
      break;
    case 0x15:
      ora(ctx, fetch_char(ctx, zero_page_x_addr(ctx)));
      break;
    case 0x16:
      asl(ctx, zero_page_x_addr(ctx), 0);
      break;
    case 0x18:
      clc(ctx);
      pc_inc = 1;
      break;
    case 0x19:
      ora(ctx, fetch_char(ctx, absolute_y_addr(ctx)));
      pc_inc = 3;
      break;
    case 0x1D:
      ora(ctx, fetch_char(ctx, absolute_x_addr(ctx)));
      pc_inc = 3;
      break;
    case 0x1E:
      asl(ctx, absolute_x_addr(ctx), 0);
      pc_inc = 3;
      break;
    case 0x20:
      jsr(ctx, absolute_addr(ctx));
      pc_inc = 0;
      break;
    case 0x21:
      and(ctx, fetch_char(ctx, indexed_indirect_addr(ctx)));
      break;
    case 0x24:
      bit(ctx, fetch_char(ctx, zero_page_addr(ctx)));
      break;
    case 0x25:
      and(ctx, fetch_char(ctx, zero_page_addr(ctx)));
      break;
    case 0x26:
      rol(ctx, zero_page_addr(ctx), 0);
      break;
    case 0x28:
      plp(ctx);
      pc_inc = 1;
      break;
    case 0x29:
      and(ctx, immediate(ctx));
      break;
    case 0x2A:
      rol(ctx, 0, 1);
      pc_inc = 1;
      break;
    case 0x2C:
      bit(ctx, fetch_char(ctx, absolute_addr(ctx)));
      pc_inc = 3;
      break;
    case 0x2D:
      and(ctx, fetch_char(ctx, absolute_addr(ctx)));
      pc_inc = 3;
      break;
    case 0x2E:
      rol(ctx, absolute_addr(ctx), 0);
      pc_inc = 3;
      break;
    case 0x30:
      bmi(ctx, relative_addr(ctx));
      break;
    case 0x31:
      and(ctx, fetch_char(ctx, indirect_indexed_addr(ctx)));
      break;
    case 0x35:
      and(ctx, fetch_char(ctx, zero_page_x_addr(ctx)));
      break;
    case 0x36:
      rol(ctx, zero_page_x_addr(ctx), 0);
      break;
    case 0x38:
      sec(ctx);
      pc_inc = 1;
      break;
    case 0x39:
      and(ctx, fetch_char(ctx, absolute_y_addr(ctx)));
      pc_inc = 3;
      break;
    case 0x3D:
      and(ctx, fetch_char(ctx, absolute_x_addr(ctx)));
      pc_inc = 3;
      break;
    case 0x3E:
      rol(ctx, absolute_x_addr(ctx), 0);
      pc_inc = 3;
      break;
    case 0x40:
      rti(ctx);
      pc_inc = 0;
      break;
    case 0x41:
      eor(ctx, fetch_char(ctx, indexed_indirect_addr(ctx)));
      break;
    case 0x45:
      eor(ctx, fetch_char(ctx, zero_page_addr(ctx)));
      break;
    case 0x46:
      lsr(ctx, zero_page_addr(ctx), 0);
      break;
    case 0x48:
      pha(ctx);
      pc_inc = 1;
      break;
    case 0x49:
      eor(ctx, immediate(ctx));
      break;
    case 0x4A:
      lsr(ctx, 0, 1);
      pc_inc = 1;
      break;
    case 0x4C:
      jmp(ctx, absolute_addr(ctx));
      pc_inc = 0;
      break;
    case 0x4D:
      eor(ctx, fetch_char(ctx, absolute_addr(ctx)));
      pc_inc = 3;
      break;
    case 0x4E:
      lsr(ctx, absolute_addr(ctx), 0);
      pc_inc = 3;
      break;
    case 0x50:
      bvc(ctx, relative_addr(ctx));
      break;
    case 0x51:
      eor(ctx, fetch_char(ctx, indirect_indexed_addr(ctx)));
      break;
    case 0x55:
      eor(ctx, fetch_char(ctx, zero_page_x_addr(ctx)));
      break;
    case 0x56:
      lsr(ctx, zero_page_x_addr(ctx), 0);
      break;
    case 0x58:
      cli(ctx);
      pc_inc = 1;
      break;
    case 0x59:
      eor(ctx, fetch_char(ctx, absolute_y_addr(ctx)));
      pc_inc = 3;
      break;
    case 0x5D:
      eor(ctx, fetch_char(ctx, absolute_x_addr(ctx)));
      pc_inc = 3;
      break;
    case 0x5E:
      lsr(ctx, absolute_x_addr(ctx), 0);
      pc_inc = 3;
      break;
    case 0x60:
      rts(ctx);
      pc_inc = 0;
      break;
    case 0x61:
      adc(ctx, fetch_char(ctx, indexed_indirect_addr(ctx)));
      break;
    case 0x65:
      adc(ctx, fetch_char(ctx, zero_page_addr(ctx)));
      break;
    case 0x66:
      ror(ctx, zero_page_addr(ctx), 0);
      break;
    case 0x68:
      pla(ctx);
      pc_inc = 1;
      break;
    case 0x69:
      adc(ctx, immediate(ctx));
      break;
    case 0x6A:
      ror(ctx, 0, 1);
      pc_inc = 1;
      break;
    case 0x6C:
      jmp(ctx, indirect_addr(ctx));
      pc_inc = 0;
      break;
    case 0x6D:
      adc(ctx, fetch_char(ctx, absolute_addr(ctx)));
      pc_inc = 3;
      break;
    case 0x6E:
      ror(ctx, absolute_addr(ctx), 0);
      pc_inc = 3;
      break;
    case 0x70:
      bvs(ctx, relative_addr(ctx));
      break;
    case 0x71:
      adc(ctx, fetch_char(ctx, indirect_indexed_addr(ctx)));
      break;
    case 0x75:
      adc(ctx, fetch_char(ctx, zero_page_x_addr(ctx)));
      break;
    case 0x76:
      ror(ctx, zero_page_x_addr(ctx), 0);
      break;
    case 0x78:
      sei(ctx);
      pc_inc = 1;
      break;
    case 0x79:
      adc(ctx, fetch_char(ctx, absolute_y_addr(ctx)));
      pc_inc = 3;
      break;
    case 0x7D:
      adc(ctx, fetch_char(ctx, absolute_x_addr(ctx)));
      pc_inc = 3;
      break;
    case 0x7E:
      ror(ctx, absolute_x_addr(ctx), 0);
      pc_inc = 3;
      break;
    case 0x81:
      sta(ctx, indexed_indirect_addr(ctx));
      break;
    case 0x84:
      sty(ctx, zero_page_addr(ctx));
      break;
    case 0x85:
      sta(ctx, zero_page_addr(ctx));
      break;
    case 0x86:
      stx(ctx, zero_page_addr(ctx));
      break;
    case 0x88:
      dey(ctx);
      pc_inc = 1;
      break;
    case 0x8A:
      txa(ctx);
      pc_inc = 1;
      break;
    case 0x8C:
      sty(ctx, absolute_addr(ctx));
      pc_inc = 3;
      break;
    case 0x8D:
      sta(ctx, absolute_addr(ctx));
      pc_inc = 3;
      break;
    case 0x8E:
      stx(ctx, absolute_addr(ctx));
      pc_inc = 3;
      break;
    case 0x90:
      bcc(ctx, relative_addr(ctx));
      break;
    case 0x91:
      sta(ctx, indirect_indexed_addr(ctx));
      break;
    case 0x94:
      sty(ctx, zero_page_x_addr(ctx));
      break;
    case 0x95:
      sta(ctx, zero_page_x_addr(ctx));
      break;
    case 0x96:
      stx(ctx, zero_page_y_addr(ctx));
      break;
    case 0x98:
      tya(ctx);
      pc_inc = 1;
      break;
    case 0x99:
      sta(ctx, absolute_y_addr(ctx));
      pc_inc = 3;
      break;
    case 0x9A:
      txs(ctx);
      pc_inc = 1;
      break;
    case 0x9D:
      sta(ctx, absolute_x_addr(ctx));
      pc_inc = 3;
      break;
    case 0xA0:
      ldy(ctx, immediate(ctx));
      break;
    case 0xA1:
      lda(ctx, fetch_char(ctx, indexed_indirect_addr(ctx)));
      break;
    case 0xA2:
      ldx(ctx, immediate(ctx));
      break;
    case 0xA4:
      ldy(ctx, fetch_char(ctx, zero_page_addr(ctx)));
      break;
    case 0xA5:
      lda(ctx, fetch_char(ctx, zero_page_addr(ctx)));
      break;
    case 0xA6:
      ldx(ctx, fetch_char(ctx, zero_page_addr(ctx)));
      break;
    case 0xA8:
      tay(ctx);
      pc_inc = 1;
      break;
    case 0xA9:
      lda(ctx, immediate(ctx));
      break;
    case 0xAA:
      tax(ctx);
      pc_inc = 1;
      break;
    case 0xAC:
      ldy(ctx, fetch_char(ctx, absolute_addr(ctx)));
      pc_inc = 3;
      break;
    case 0xAD:
      lda(ctx, fetch_char(ctx, absolute_addr(ctx)));
      pc_inc = 3;
      break;
    case 0xAE:
      ldx(ctx, fetch_char(ctx, absolute_addr(ctx)));
      pc_inc = 3;
      break;
    case 0xB0:
      bcs(ctx, relative_addr(ctx));
      break;
    case 0xB1:
      lda(ctx, fetch_char(ctx, indirect_indexed_addr(ctx)));
      break;
    case 0xB4:
      ldy(ctx, fetch_char(ctx, zero_page_x_addr(ctx)));
      break;
    case 0xB5:
      lda(ctx, fetch_char(ctx, zero_page_x_addr(ctx)));
      break;
    case 0xB6:
      ldx(ctx, fetch_char(ctx, zero_page_y_addr(ctx)));
      break;
    case 0xB8:
      clv(ctx);
      pc_inc = 1;
      break;
    case 0xB9:
      lda(ctx, fetch_char(ctx, absolute_y_addr(ctx)));
      pc_inc = 3;
      break;
    case 0xBA:
      tsx(ctx);
      pc_inc = 1;
      break;
    case 0xBC:
      ldy(ctx, fetch_char(ctx, absolute_x_addr(ctx)));
      pc_inc = 3;
      break;
    case 0xBD:
      lda(ctx, fetch_char(ctx, absolute_x_addr(ctx)));
      pc_inc = 3;
      break;
    case 0xBE:
      ldx(ctx, fetch_char(ctx, absolute_y_addr(ctx)));
      pc_inc = 3;
      break;
    case 0xC0:
      cpy(ctx, immediate(ctx));
      break;
    case 0xC1:
      cmp(ctx, fetch_char(ctx, indexed_indirect_addr(ctx)));
      break;
    case 0xC4:
      cpy(ctx, fetch_char(ctx, zero_page_addr(ctx)));
      break;
    case 0xC5:
      cmp(ctx, fetch_char(ctx, zero_page_addr(ctx)));
      break;
    case 0xC6:
      dec(ctx, zero_page_addr(ctx));
      break;
    case 0xC8:
      iny(ctx);
      pc_inc = 1;
      break;
    case 0xC9:
      cmp(ctx, immediate(ctx));
      break;
    case 0xCA:
      dex(ctx);
      pc_inc = 1;
      break;
    case 0xCC:
      cpy(ctx, fetch_char(ctx, absolute_addr(ctx)));
      pc_inc = 3;
      break;
    case 0xCD:
      cmp(ctx, fetch_char(ctx, absolute_addr(ctx)));
      pc_inc = 3;
      break;
    case 0xCE:
      dec(ctx, absolute_addr(ctx));
      pc_inc = 3;
      break;
    case 0xD0:
      bne(ctx, relative_addr(ctx));
      break;
    case 0xD1:
      cmp(ctx, fetch_char(ctx, indirect_indexed_addr(ctx)));
      break;
    case 0xD5:
      cmp(ctx, fetch_char(ctx, zero_page_x_addr(ctx)));
      break;
    case 0xD6:
      dec(ctx, zero_page_x_addr(ctx));
      break;
    case 0xD8:
      cld(ctx);
      pc_inc = 1;
      break;
    case 0xD9:
      cmp(ctx, fetch_char(ctx, absolute_y_addr(ctx)));
      pc_inc = 3;
      break;
    case 0xDD:
      cmp(ctx, fetch_char(ctx, absolute_x_addr(ctx)));
      pc_inc = 3;
      break;
    case 0xDE:
      dec(ctx, absolute_x_addr(ctx));
      pc_inc = 3;
      break;
    case 0xE0:
      cpx(ctx, immediate(ctx));
      break;
    case 0xE1:
      sbc(ctx, fetch_char(ctx, indexed_indirect_addr(ctx)));
      break;
    case 0xE4:
      cpx(ctx, fetch_char(ctx, zero_page_addr(ctx)));
      break;
    case 0xE5:
      sbc(ctx, fetch_char(ctx, zero_page_addr(ctx)));
      break;
    case 0xE6:
      inc(ctx, zero_page_addr(ctx));
      break;
    case 0xE8:
      inx(ctx);
      pc_inc = 1;
      break;
    case 0xE9:
      sbc(ctx, immediate(ctx));
      break;
    case 0xEC:
      cpx(ctx, fetch_char(ctx, absolute_addr(ctx)));
      pc_inc = 3;
      break;
    case 0xED:
      sbc(ctx, fetch_char(ctx, absolute_addr(ctx)));
      pc_inc = 3;
      break;
    case 0xEE:
      inc(ctx, absolute_addr(ctx));
      pc_inc = 3;
      break;
    case 0xF0:
      beq(ctx, relative_addr(ctx));
      break;
    case 0xF1:
      sbc(ctx, fetch_char(ctx, indirect_indexed_addr(ctx)));
      break;
    case 0xF5:
      sbc(ctx, fetch_char(ctx, zero_page_x_addr(ctx)));
      break;
    case 0xF6:
      inc(ctx, zero_page_x_addr(ctx));
      break;
    case 0xF8:
      sed(ctx);
      pc_inc = 1;
      break;
    case 0xF9:
      sbc(ctx, fetch_char(ctx, absolute_y_addr(ctx)));
      pc_inc = 3;
      break;
    case 0xFD:
      sbc(ctx, fetch_char(ctx, absolute_x_addr(ctx)));
      pc_inc = 3;
      break;
    case 0xFE:
      inc(ctx, absolute_x_addr(ctx));
      pc_inc = 3;
      break;
    default:
      pc_inc = 1;
  }
  ctx->pc = ctx->pc + pc_inc;
  return cycle_counts[inst];
}
