#ifndef MAC_H
#define MAC_H

#include "util.h"

enum OPCODE {
  OP_SETR_IMM, // sets row value from immediate
  OP_SETC_IMM, // sets col value from immediate
  OP_SETT,     // sets register as temp
  OP_TSET,     // sets temp register value from register
  OP_TSETL,    // TSET if flag_lo is set
  OP_TSETE,    // TSET if flag_eq is set
  OP_TSETG,    // TSET if flag_gr is set
  OP_TSET_IMM, // sets temp register value from immediate

  OP_TCMP, // compares temp register with register and sets flags

  OP_TADD,     // adds other register to temp register
  OP_TSUB,     // subtracts register from temp register
  OP_TMUL,     // multiplies temp register by register
  OP_TDIV,     // divides temp register by register
  OP_reserved, // reserved

  OP_TGET, // gets temp register value from stdin
  OP_TPUT, // puts temp register value to stdout
};

#define OPCODE_MASK 0xF

struct Machine {
  union {
    long long all[1 << 12];
    long long cp;
  } regs;

  unsigned tp : 12;
  unsigned row : 4;
  unsigned col : 4;

  struct {
    unsigned lo : 1;
    unsigned eq : 1;
    unsigned gr : 1;
  } flags;
};

void mac_init(struct Machine *restrict mac);

enum EXECUTION_ERR {
  EERR_INVALID_INSTRUCTION = 1,
  EERR_INVALID_TEXT_ADDRESS,
  EERR_DIVISION_BY_ZERO,
};

enum EXECUTION_ERR mac_execute(struct Machine *restrict mac, const char *text,
                               off_t sz);

#endif
