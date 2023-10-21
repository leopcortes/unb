n = int(input())
t = int(input())

listas = []

for i in range(n):
    lista = list(map(int, input().split()))
    listas.append(lista)
    
def comparar(lista):
    return (lista[t], sum(lista))
    
listas_ordenadas = sorted(listas, key=comparar)

for lista in listas_ordenadas:
    print(' '.join(map(str, lista)))