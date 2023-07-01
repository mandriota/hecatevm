#ifndef DEBUG_H
#define DEBUG_H

const char *opcodes_stringify[] = {"SETR_IMM", "SETC_IMM", "SETT",  "TSET",
                                   "TSETL",    "TSETE",    "TSETG", "TSET_IMM",
                                   "TCMP",     "TADD",     "TSUB",  "TMUL",
                                   "TDIV",     "TGET",     "TPUT",  ""};

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
