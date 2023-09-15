package main

import (
	"bufio"
	"crypto/rand"
	"fmt"
	"log"
	"math/big"
	"os"
)

func main() {
	words := []string{
		"SETR.IMM    ; sets row value from immediate",
		"SETC.IMM    ; sets col value from immediate",
		"SETT        ; sets register as temp",
		"TSET        ; sets temp register value from register",
		"TSET.L      ; TSET if flag_lo is set",
        "TSET.E      ; TSET if flag_eq is set",
		"TSET.G      ; TSET if flag_gr is set",
		"TSET.IMM    ; sets temp register value from immediate",
		"TCMP        ; compares temp register with register and sets flags",
		"TADD        ; adds other register to temp register",
		"TSUB        ; subtracts register from temp register",
		"TMUL        ; multiplies temp register by register",
		"TDIV        ; divides temp register by register",
		"TGET        ; gets temp register value from stdin",
		"TPUT        ; puts temp register value to stdout",
	}

	fs, err := os.Create("tests/random.asm")
	if err != nil {
		log.Fatalln(err)
	}
	defer fs.Close()

	w := bufio.NewWriter(fs)
	defer w.Flush()

	total := 0
	for total < 9766641 {
		rn, err := rand.Int(rand.Reader, big.NewInt(int64(len(words))))
		if err != nil {
			log.Fatalln(err)
		}

		rn2, err := rand.Int(rand.Reader, big.NewInt(16))
		if err != nil {
			log.Fatalln(err)
		}

		n, err := fmt.Fprintf(w, "\t%X.%s\n", rn2.Int64(), words[rn.Int64()])
		if err != nil {
			log.Fatalln(err)
		}
		total += n
	}
}
