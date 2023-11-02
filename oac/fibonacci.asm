.text

start:
	li  a0, 10        # a0 = n

	li  a1, 0         # a1 = 0
	beq a0, a1, done  # if(n=1): encerra
    
	li  a2, 1         # a2 = 1
	beq a0, a2, done  # if(n=2): encerra

	li  t0, 1         # cont = 1
loop:
	# Fibonacci(n) = Fibonacci(n-1) + Fibonacci(n-2)
	add a3, a1, a2    # res = a1 + a2
	mv  a1, a2        # a1 = a2
	mv  a2, a3        # a2 = res
    
	addi t0, t0, 1    # cont += 1
	beq  t0, a0, done # if(cont=n): encerra
	j    loop         # else: retorna ao inicio do loop

done:
	li a7, 1          # Código de servico 1 para imprimir um inteiro
	mv a0, a3         # print(a0)
	ecall

	li a7, 10         # Código de servico 10 para encerrar o programa
	ecall

# REGISTRADORES
# a0 = n
# a1 = 1
# a2 = 2
# a3 = resultado
# t0 = contador