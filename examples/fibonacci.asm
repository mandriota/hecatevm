	;; input
	2.SETT
	0.TGET

	4.SETT
	1.TSET.IMM

	2.SETT
	4.TADD

	5.SETT
	0.TSET.IMM

	;; y
	6.SETT
	1.TSET.IMM

	;; 7 - x

	;; 8 - tmp

	;; label
	3.SETT
	0.TSET

	8.SETT
	7.TSET

	7.SETT
	6.TADD

	6.SETT
	8.TSET

	2.SETT
	4.TSUB
	5.TCMP
	
	;; jump to label
	0.SETT
	3.TSET.G

	;; output
	6.SETT
	0.TPUT
