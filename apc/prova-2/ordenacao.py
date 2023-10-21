def ordenacao(x):
	lista_ordenada = []
	for _ in range(len(x)):
		menor = min(x)
		lista_ordenada.append(menor)
		x.remove(menor)

	return lista_ordenada

print(ordenacao([4, 6, 10, 1000, 1, 0, 0, 0, 2]))
print(ordenacao([10000, 1000, 100, 10, 1]))
print(ordenacao([45, 12, 4967, 632, 9, 8321, 0, 1]))