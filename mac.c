#include "mac.h"
#include "util.h"

// #include "debug.h"

void mac_init(struct Machine *restrict mac) { memset(mac, 0, sizeof(*mac)); }

enum EXECUTION_ERR mac_execute(struct Machine *restrict mac, const char *text,
                               off_t sz) {
  if (mac == NULL)
    fatal("mac should not be NULL");

#ifdef DEBUG_H
  mac_print_state(mac);
#endif

  if (sz == 0)
    return 0;

  if (text == NULL)
    fatal("sz is not zero, but text is NULL");

#ifdef DEBUG_H
  int i = -10000; // limit number of iterations to 10000
#endif

  while (mac->regs.cp >= 0 && mac->regs.cp < sz) {
    unsigned char op = text[mac->regs.cp] & OPCODE_MASK;
    unsigned char arg = (unsigned char)text[mac->regs.cp] >> 4;
    ++mac->regs.cp;

#ifdef DEBUG_H
    printf("CALLING\t%s\t%d\n", opcodes_stringify[op], arg);
#endif

    switch (op) {
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
      mac->regs.all[mac->tp] = scan_num();
      break;
    case OP_TPUT:
      fwrite("output: ", 1, 8, stdout);
      print_num(mac->regs.all[mac->tp]);
      putchar_unlocked('\n');
      break;
    default:
      return EERR_INVALID_INSTRUCTION;
    }

#ifdef DEBUG_H
    mac_print_state(mac);
    ++i;
    if (i == 0)
      break;
#endif
  }

  if (mac->regs.cp != sz)
    return EERR_INVALID_TEXT_ADDRESS;

  return 0;
}
