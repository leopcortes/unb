.data
blk_in:
	.word 0, 1, 2, 3
blk_out:
	.word 0, 0, 0, 0
keys:	
	.word 1, 2, 3, 4, 5, 6
mask:
	.word 0xFFFF
espaco: 
	.ascii "  "

.text
.globl main
.globl idea_round
.globl mult

main:
	# Inicialização dos registradores
	la a0, blk_in
	la a1, blk_out
	la a2, keys

	jal a3, idea_round # Chama a função idea_round

	# Impressão dos valores finais
	li s10, 0 # Contador i = 0
	li s11, 4 # Limite do loop = 4

loop:
	lw s9, 0(a1)       # Carrega um valor de blk_out[i] em a3
    
	li a7, 1           # Código de serviço 1 para imprimir um inteiro
	mv a0, s9
	ecall
	
	li a7, 4           # Código de serviço 4 para imprimir um ascii
	la a0, espaco
	ecall

	addi a1, a1, 4     # Avança para o próximo elemento de blk_out
	addi s10, s10, 1   # Incrementa i

	bne s10, s11, loop # Volta para o início do loop se i != 4

	li a7, 10          # Código de serviço 10 para encerrar o programa
	ecall

idea_round:
	lw s0, 0(a0)   # Carrega word1
	lw s1, 4(a0)   # Carrega word2
	lw s2, 8(a0)   # Carrega word3
	lw s3, 12(a0)  # Carrega word4
	lw s8, mask    # Carrega a máscara 0xFFFF
	
	## word1 = mul(word1, *key_ptr++)
	lw  s4, 0(a2)  # Carrega a primeira chave
	mv  t3, s0     # x = word1
	mv  t4, s4     # y = key1
	jal a4, mult   # mult(word1, key1)
	mv  s0, s7     # word1 = x
	
	## word2 = LSW16(word2 + *key_ptr++)
	lw  s4, 4(a2)  # Carrega a segunda chave
	add t1, s1, s4 # word2 + key2
	and s1, t1, s8 # word2 = (word2 + key2) & 0xFFFF
	
	## word3 = LSW16(word3 + *key_ptr++)
	lw  s4, 8(a2)  # Carrega a terceira chave
	add t1, s2, s4 # word3 + key3
	and s2, t1, s8 # word3 = (word3 + key3) & 0xFFFF
	
	## word4 = mul(word4, *key_ptr++)
	lw  s4, 12(a2) # Carrega a quarta chave
	mv  t3, s3     # x = word4
	mv  t4, s4     # y = key4
	jal a4, mult   # mult(word4, key4)
	mv  s3, s7     # word4 = x
	
	xor s6, s0, s2 # t2 = word1 ^ word3
	
	## t2 = mul(t2, *key_ptr++)
	lw  s4, 16(a2) # Carrega a quinta chave
	mv  t3, s6     # x = t2
	mv  t4, s4     # y = key5
	jal a4, mult   # mult(t2, key5)
	mv  s6, s7     # t2 = x
	
	## t1 = LSW16(t2 + (word2 ^ word4))
	xor t0, s1, s3 # temp0 = word2 ^ word4
	add t1, s6, t0 # temp1 = t2 + temp0(word2 ^ word4)
	and s5, t1, s8 # t1 = (t2 + (word2 ^ word4)) & 0xFFFF
	
	## t1 = mul(t1, *key_ptr++)
	lw  s4, 20(a2) # Carrega a sexta chave
	mv  t3, s5     # x = t1
	mv  t4, s4     # y = key6
	jal a4, mult   # mult(t1, key6)
	mv  s5, s7     # t1 = x
	
	## t2 = LSW16(t1 + t2)
	add t1, s5, s6 # t1 + t2
	and s6, t1, s8 # t2 = (t1 + t2) & 0xFFFF
		
	xor s0, s0, s5 # word1 = word1 ^ t1
	xor s3, s3, s6 # word4 = word4 ^ t2
	
	xor s6, s6, s1 # t2 = t2 ^ word2
	xor s1, s2, s5 # word2 = word3 ^ t1
	mv  s2, s6     # word3 = t2

	# Armazena as palavras de saída
	sw s0, 0(a1)   # word1 = blk_out_ptr[0]
	sw s1, 4(a1)   # word2 = blk_out_ptr[1]
	sw s2, 8(a1)   # word3 = blk_out_ptr[2]
	sw s3, 12(a1)  # word4 = blk_out_ptr[3]

	jalr x0, 0(a3) # Retorna para main

mult:
	mul t2, t3, t4          # p = x * y

	beqz t2, resultado_zero # if p == 0

	# Se o resultado não for zero
	li t5, 16
	srl t3, t2, t5          # x = p >> 16
	mv t4, t2               # y = p
	sub t3, t4, t3          # x = y - x

	bgeu t4, t3, resultado_final # if y >= x { return x }

	# Se y < x, x = x + 65537
	li t6, 0x10001
	add t3, t3, t6
	j resultado_final

resultado_zero:
	# if p == 0 { x = 65537 - x - y }
	li t6, 0x10001
	sub t3, t6, t3
	sub t3, t3, t4

resultado_final:
	and s7, t3, s8 # x = x & 0xFFFF (LSW16)
	jalr x0, 0(a4) # Retorna para chamada da função mult

# REGISTRADORES:
# a0: endereço de blk_in_ptr (array entrada)
# a1: endereço de blk_out_ptr (array saída)
# a2: endereço de key_ptr (array chaves)
# a3: endereço de retorno da idea_round
# a4: endereço de retorno da mult
# a5: 
# a5: 
# a7: serviço
#
# t0: auxiliar (word2 ^ word4)
# t1: auxiliar (word + key em operações LSW16)
# t2: p (em mult)
# t3: x (em mult)
# t4: y (em mult)
# t5: 16 (decimal)
# t6: 0x10001 (65537 em decimal)
#
# s0: word 1
# s1: word 2
# s2: word 3
# s3: word 4
# s4: chaves
# s5: t1 (c)
# s6: t2 (c)
# s7: auxiliar (x no final de mult)
# s8: mask 0xFFFF
# s9: valor da saída a ser impresso
# s10: contador i
# s11: limite do loop (4)

# ETAPAS (teoria):
# X1 * K1
# X2 + K2
# X3 + K3
# X4 * K4
# Etapa 1 ^ Etapa 3
# Etapa 2 ^ Etapa 4
# Etapa 5 * K5
# Etapa 6 + Etapa 7
# Etapa 8 * K6
# Etapa 7 + Etapa 9
# Etapa 1 ^ Etapa 9
# Etapa 3 ^ Etapa 9
# Etapa 2 ^ Etapa 10
# Etapa 4 ^ Etapa 10
