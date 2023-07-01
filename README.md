# HecateVM
Tiny register-based bytecode VM written in C.

## Instructions
| code | name     | description                                               |
|:----:|:---------|:----------------------------------------------------------|
| 0x0  | SETR_IMM | sets row value from immediate                             |
| 0x1  | SETC_IMM | sets col value from immediate                             |
| 0x2  | SETT     | sets register as temp                                     |
| 0x3  | TSET     | sets temp register value from register                    |
| 0x4  | TSETL    | TSET if flag_lo is set                                    |
| 0x5  | TSETE    | TSET if flag_eq is set                                    |
| 0x6  | TSETG    | TSET if flag_gr is set                                    |
| 0x7  | TSET_IMM | sets temp register value from immediate                   |
| 0x8  | TCMP     | compares temp register with register and sets flags       |
| 0x9  | TADD     | adds register to temp register                            |
| 0xA  | TSUB     | subtracts register from temp register                     |
| 0xB  | TMUL     | multiplies temp register by register                      |
| 0xC  | TDIV     | divides temp register by register                         |
| 0xD  |          | reserved                                                  |
| 0xE  | TGET     | gets temp register value from stdin                       |
| 0xF  | TPUT     | puts temp register value to stdout                        |
