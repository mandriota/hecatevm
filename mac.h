#ifndef MAC_H
#define MAC_H

#include "util.h"

enum OPCODE {
  SETR_IMM, // sets row value from immediate
  SETC_IMM, // sets col value from immediate
  SETT,     // sets register as temp
  TSET,     // sets temp register value from register
  TSETL,    // TSET if flag_lo is set
  TSETE,    // TSET if flag_eq is set
  TSETG,    // TSET if flag_gr is set
  TSET_IMM, // sets temp register value from immediate

  TCMP, // compares temp register with register and sets flags

  TADD,              // adds other register to temp register
  TSUB,              // subtracts register from temp register
  TMUL,              // multiplies temp register by register
  TDIV,              // divides temp register by register
  opcode_reserved_0, // reserved

  TGET, // gets temp register value from stdin
  TPUT, // puts temp register value to stdout
};

#define OPCODE_MASK 0xF

struct Machine {
  long long regs[1 << 12];
  unsigned row : 4;
  unsigned col : 4;
  unsigned tp : 12;
  unsigned flag_lo : 1;
  unsigned flag_eq : 1;
  unsigned flag_gr : 1;
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
