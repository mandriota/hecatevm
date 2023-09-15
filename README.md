# HecateVM
Tiny register-based bytecode VM written in C.

## Instructions
| code | name     | description                                               |
|:----:|:---------|:----------------------------------------------------------|
| 0x0  | SETR.IMM | sets row value from immediate                             |
| 0x1  | SETC.IMM | sets col value from immediate                             |
| 0x2  | SETT     | sets register as temp                                     |
| 0x3  | TSET     | sets temp register value from register                    |
| 0x4  | TSET.L   | TSET if flag.lo is set                                    |
| 0x5  | TSET.E   | TSET if flag.eq is set                                    |
| 0x6  | TSET.G   | TSET if flag.gr is set                                    |
| 0x7  | TSET.IMM | sets temp register value from immediate                   |
| 0x8  | TCMP     | compares temp register with register and sets flags       |
| 0x9  | TADD     | adds register to temp register                            |
| 0xA  | TSUB     | subtracts register from temp register                     |
| 0xB  | TMUL     | multiplies temp register by register                      |
| 0xC  | TDIV     | divides temp register by register                         |
| 0xD  |          | reserved                                                  |
| 0xE  | TGET     | gets temp register value from stdin                       |
| 0xF  | TPUT     | puts temp register value to stdout                        |

## Installation

- Clone repo:
```sh
# Clone and change directory to repo
git clone https://github.com/mandriota/hecatevm
cd hecatevm

# Build HecateVM
make

# Add binary to your system bin directory or to PATH:
link bin/hcvm /usr/local/bin/hcvm
```

## Example of Factorial
```asm
	;; ./examples/factorial.asm
	
	;; r = 1
	3.SETT
    1.TSET.IMM

	;; const.
    5.SETT
    1.TSET.IMM

	;; input n
    1.SETT
    0.TGET

	;; i = 2
    4.SETT
    2.TSET.IMM

	;; do
    2.SETT
	0.TSET						; save current address

	;; r *= i
    3.SETT
    4.TMUL

	;; i++
    4.SETT
    1.TCMP
    5.TADD

	;; while (i < n)
    0.SETT 						; jump to saved address
    2.TSET.L

	;; print r
    3.SETT
    0.TPUT
```

### Assembling and running
```sh
hcvm asm -o factorial.hcvm factorial.asm
hcvm factorial.hcvm
```
(You can also use `hcvm run factorial` command)
