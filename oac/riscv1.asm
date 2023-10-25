.data
valor: 	.word 10

.text
	la a0, valor
	lw t1, 0(a0)
	
	li t1, 100
