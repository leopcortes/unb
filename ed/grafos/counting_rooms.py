def dfs(i, j):
    # fora do grafo
    if i < 0 or i >= n or j < 0 or j >= m: return

    # quadrado ja visto
    elif vistos[i][j]: return

    # parede encontrada
    elif grafo[i][j] == '#': return 

    # marca o quadrado atual como visitado
    vistos[i][j] = True

    # movimentos: baixo, direita, cima e esquerda
    movimentos = [
        (1,0),(0,1),(-1,0),(0,-1)
    ]

    # proximo quadrado
    for x,y in movimentos:
        dfs(i+x,j+y)

n,m = map(int, input().split())
grafo = []
for _ in range(n):
    linha = input()
    grafo.append(linha)

vistos = []
for _ in range(n):
    linha = [False] * m
    vistos.append(linha)

quartos = 0
for i in range(n):
    for j in range(m):
        # quadrado de quarto encontrado nao contabilizado
        if not vistos[i][j] and grafo[i][j] == '.':
            quartos += 1
            dfs(i,j)

print(quartos)