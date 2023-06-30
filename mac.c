#include "mac.h"

// #include "debug.h"

void mac_init(struct Machine *restrict mac) {
  mac->row = 0;
  mac->col = 0;
  mac->tp = 0;
  memset(mac->regs, 0, sizeof(mac->regs));
}

enum EXECUTION_ERR mac_execute(struct Machine *restrict mac, const char *text,
                               off_t sz) {
  if (mac == NULL)
    fatal("Machine should not be NULL");

#ifdef DEBUG_H
  m_print_state(mac);
#endif

  if (sz == 0)
    return 0;

  int i = 0;

  while (mac->regs[0] >= 0 && mac->regs[0] < sz && i < 10) {
    unsigned char arg = (unsigned char)text[mac->regs[0]] >> 4;

#ifdef DEBUG_H
    printf("CALLING\t%s\t%d\n",
           opcodes_stringify[text[mac->regs[0]] & OPCODE_MASK], arg);
#endif

    switch (text[mac->regs[0]] & OPCODE_MASK) {
    case SETR_IMM:
      mac->row = arg;
      break;
    case SETC_IMM:
      mac->col = arg;
      break;
    case SETT:
      mac->tp = 0xFF * mac->row + 0xF * mac->col + arg;
      break;
    case TSET:
      mac->regs[mac->tp] = mac->regs[arg];
      break;
    case TSETL:
      if (mac->flag_lo)
        mac->regs[mac->tp] = mac->regs[arg];
      break;
    case TSETE:
      if (mac->flag_eq)
        mac->regs[mac->tp] = mac->regs[arg];
      break;
    case TSETG:
      if (mac->flag_gr)
        mac->regs[mac->tp] = mac->regs[arg];
      break;
    case TSET_IMM:
      mac->regs[mac->tp] = arg;
      break;
    case TCMP:
      mac->flag_lo = mac->regs[mac->tp] < arg;
      mac->flag_eq = mac->regs[mac->tp] == arg;
      mac->flag_gr = mac->regs[mac->tp] > arg;
      break;
    case TADD:
      mac->regs[mac->tp] += mac->regs[arg];
      break;
    case TSUB:
      mac->regs[mac->tp] -= mac->regs[arg];
      break;
    case TMUL:
      mac->regs[mac->tp] *= mac->regs[arg];
      break;
    case TDIV:;
      long long v = mac->regs[mac->tp] -= mac->regs[arg];
      if (v == 0)
        return EERR_DIVISION_BY_ZERO;
      mac->regs[mac->tp] /= v;
      break;
    case TGET:
      scanf("%lld", &mac->regs[mac->tp]);
      break;
    case TPUT:
      fwrite("output: ", 1, 8, stdout);
      print_num(mac->regs[mac->tp]);
      putchar_unlocked('\n');
      break;
    default:
      return EERR_INVALID_INSTRUCTION;
      break;
    }
    ++mac->regs[0];
    ++i;

#ifdef DEBUG_H
    m_print_state(mac);
#endif
  }

  if (mac->regs[0] != sz)
    return EERR_INVALID_TEXT_ADDRESS;

  return 0;
}
