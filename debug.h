#ifndef DEBUG_H
#define DEBUG_H

const char *opcodes_stringify[] = {"SETR_IMM", "SETC_IMM", "SETT",  "TSET",
                                   "TSETL",    "TSETE",    "TSETG", "TSET_IMM",
                                   "TCMP",     "TADD",     "TSUB",  "TMUL",
                                   "TDIV",     "TGET",     "TPUT",  ""};

#define mac_print_state(mac)                                                   \
  printf("============= STATE =============\n");                               \
  printf("flags: lo=%d; eq=%d; gr=%d;\n", mac->flag_lo, mac->flag_eq,          \
         mac->flag_gr);                                                        \
  printf("row=%d\n", mac->row);                                                \
  printf("col=%d\n", mac->col);                                                \
  printf("temp register ptr: %d\n", mac->tp);                                  \
  printf("current pos: %lld\n", mac->regs[0]);                                 \
  printf("=================================\n");

#endif
