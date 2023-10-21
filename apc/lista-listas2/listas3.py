N, M = map(int, input().split())
Q = int(input())

mapa = [[0] * M for _ in range(N)]

projeteis = []
for _ in range(Q):
    x, y = map(int, input().split())
    x -= 1
    y -= 1
    projeteis.append((x, y))

for x, y in projeteis:
    mapa[x][y] += 1
    for i in range(N):
        if i != x:
            mapa[i][y] += 1
    for j in range(M):
        if j != y:
            mapa[x][j] += 1

maior_profundidade = max(max(linha) for linha in mapa)
cont = sum(linha.count(maior_profundidade) for linha in mapa)

print(cont)