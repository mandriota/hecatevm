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
