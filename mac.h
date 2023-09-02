// Copyright 2023 Mark Mandriota
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#ifndef MAC_H
#define MAC_H

#include <sys/types.h>

enum OPCODE {
  OP_SETR_IMM, // sets row value from immediate
  OP_SETC_IMM, // sets col value from immediate
  OP_SETT,     // sets register as temp
  OP_TSET,     // sets temp register value from register
  OP_TSET_L,    // TSET if flag_lo is set
  OP_TSET_E,    // TSET if flag_eq is set
  OP_TSET_G,    // TSET if flag_gr is set
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

enum EXECUTION_RESULT {
  ER_OK,
  ER_ERR_INVALID_INSTRUCTION,
  ER_ERR_INVALID_TEXT_ADDRESS,
  ER_ERR_DIVISION_BY_ZERO,
};

enum EXECUTION_RESULT mac_execute(struct Machine *restrict mac, const char *text,
                               off_t sz);

#endif
