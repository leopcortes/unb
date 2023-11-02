.text

start:
	li  a0, 10        # a0 = n

	li  a1, 0         # a1 = 0
	beq a0, a1, done  # if(n=1): encerra
    
	li  a2, 1         # a2 = 1
	beq a0, a2, done  # if(n=2): encerra

	li  t0, 0         # cont = 0
	
	jal t1, fibonacci_recursiva

done:
	li a7, 1          # Código de servico 1 para imprimir um inteiro
	mv a0, a3         # print(a0)
	ecall

	li a7, 10         # Código de servico 10 para encerrar o programa
	ecall

fibonacci_recursiva:

	# Caso recursivo:
	addi a0, a0, -1          # n = n - 1
	mv   a4, a1              # Salve o resultado atual em a4
	mv   a1, a2              # a1 = resultado anterior
	mv   a2, a4              # a2 = resultado atual

	addi a3, a3, 1           # Incrementar contador

	j fibonacci_recursiva    # Chamada recursiva

	# Após o retorno da chamada recursiva, some a1 e a2 e retorne o resultado.
	add a1, a1, a2
	jalr x0, 0(t1)

# REGISTRADORES
# a0 = n
# a1 = 1
# a2 = 2
# a3 = resultado
# t0 = contador