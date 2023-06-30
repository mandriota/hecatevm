#include "mac.h"

// #include "debug.h"

void mac_init(struct Machine *restrict mac) {
  mac->row = 0;
  mac->col = 0;
  mac->tp = 0;
  memset(mac->regs.all, 0, sizeof(mac->regs));
}

enum EXECUTION_ERR mac_execute(struct Machine *restrict mac, const char *text,
                               off_t sz) {
  if (mac == NULL)
    fatal("Machine should not be NULL");

#ifdef DEBUG_H
  mac_print_state(mac);
#endif

  if (sz == 0)
    return 0;

  int i = 0;

  while (mac->regs.cp >= 0 && mac->regs.cp < sz && i < 10) {
    unsigned char arg = (unsigned char)text[mac->regs.cp] >> 4;

#ifdef DEBUG_H
    printf("CALLING\t%s\t%d\n",
           opcodes_stringify[text[mac->regs.cp] & OPCODE_MASK], arg);
#endif

    switch (text[mac->regs.cp] & OPCODE_MASK) {
    case OP_SETR_IMM:
      mac->row = arg;
      break;
    case OP_SETC_IMM:
      mac->col = arg;
      break;
    case OP_SETT:
      mac->tp = 0xFF * mac->row + 0xF * mac->col + arg;
      break;
    case OP_TSET:
      mac->regs.all[mac->tp] = mac->regs.all[arg];
      break;
    case OP_TSETL:
      if (mac->flags.lo)
        mac->regs.all[mac->tp] = mac->regs.all[arg];
      break;
    case OP_TSETE:
      if (mac->flags.eq)
        mac->regs.all[mac->tp] = mac->regs.all[arg];
      break;
    case OP_TSETG:
      if (mac->flags.gr)
        mac->regs.all[mac->tp] = mac->regs.all[arg];
      break;
    case OP_TSET_IMM:
      mac->regs.all[mac->tp] = arg;
      break;
    case OP_TCMP:
      mac->flags.lo = mac->regs.all[mac->tp] < arg;
      mac->flags.eq = mac->regs.all[mac->tp] == arg;
      mac->flags.gr = mac->regs.all[mac->tp] > arg;
      break;
    case OP_TADD:
      mac->regs.all[mac->tp] += mac->regs.all[arg];
      break;
    case OP_TSUB:
      mac->regs.all[mac->tp] -= mac->regs.all[arg];
      break;
    case OP_TMUL:
      mac->regs.all[mac->tp] *= mac->regs.all[arg];
      break;
    case OP_TDIV:;
      long long denom = mac->regs.all[arg];
      if (denom == 0)
        return EERR_DIVISION_BY_ZERO;
      mac->regs.all[mac->tp] /= denom;
      break;
    case OP_reserved:
      return EERR_INVALID_INSTRUCTION;
    case OP_TGET:
      fwrite("input: ", 1, 7, stdout);
      scanf("%lld", &mac->regs.all[mac->tp]);
      break;
    case OP_TPUT:
      fwrite("output: ", 1, 8, stdout);
      print_num(mac->regs.all[mac->tp]);
      putchar_unlocked('\n');
      break;
    default:
      return EERR_INVALID_INSTRUCTION;
    }
    ++mac->regs.cp;
    ++i;

#ifdef DEBUG_H
    mac_print_state(mac);
#endif
  }

  if (mac->regs.cp != sz)
    return EERR_INVALID_TEXT_ADDRESS;

  return 0;
}
