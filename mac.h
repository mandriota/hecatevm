#ifndef MAC_H
#define MAC_H
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#include "util.h"

enum OPCODE {
  SETR_IMM, // sets row to immidiate value
  SETC_IMM, // sets colon to immidiate value
  SETT,     // sets temp register

  TSET,     // sets register as temp
  TSETL,    // sets temp register value from other register if flag l is set
  TSETE,    // sets temp register value from other register if flag e is set
  TSETG,    // sets temp register value from other register if flag g is set
  TSET_IMM, // sets temp register to immidiate value

  TCMP, // compares temp register with other value

  TADD, // adds other register to temp register
  TSUB, // subs other register from temp register
  TMUL, // multiplis temp register by other register
  TDIV, // dividies temp register by other register

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

void m_init(struct Machine *__restrict mac);

enum EXECUTION_ERR {
  EERR_INVALID_INSTRUCTION = 1,
  EERR_INVALID_TEXT_ADDRESS,
  EERR_DIVISION_BY_ZERO,
};

enum EXECUTION_ERR m_execute(struct Machine *__restrict mac, const char *text,
                             off_t sz);

#endif
