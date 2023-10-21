def contagem_recursiva(n): # 
	if n == 0: # Caso de parada
		return
	contagem_recursiva(n-1) # Recursão inversa (primeiro inverte depois imprime)
	print(n) # impressão

contagem_recursiva(10)
contagem_recursiva(1)
contagem_recursiva(2)