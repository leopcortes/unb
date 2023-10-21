# Imprimir chamada em ordem alfabetica decrescente

n = int(input())
chamada = []

for i in range(n):
    nome = input()
    chamada.append(nome)
    
chamada.sort(reverse=True)

for i in range(n):
    print(chamada[i])