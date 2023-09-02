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
#ifndef DEBUG_H
#define DEBUG_H

const char *opcodes_stringify[16] = {"SETR.IMM", "SETC.IMM", "SETT",   "TSET",
                                     "TSET.L",   "TSET.E",   "TSET.G", "TSET.IMM",
                                     "TCMP",     "TADD",     "TSUB",   "TMUL",
                                     "TDIV",     "",         "TGET",   "TPUT"};

#define mac_print_state(mac)                                                   \
  printf("============= STATE =============\n"                                 \
         "flags: lo=%d; eq=%d; gr=%d;\n"                                       \
         "row=%d\n"                                                            \
         "col=%d\n"                                                            \
         "temp register pointer (tp): %d\n"                                    \
         "code pointer (cp): %lld\n"                                           \
         "=================================\n",                                \
         mac->flags.lo, mac->flags.eq, mac->flags.gr, mac->row, mac->col,      \
         mac->tp, mac->regs.cp);

#endif
