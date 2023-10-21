m, n = map(int, input().split())

sala = []
for _ in range(m):
    linha = list(map(int, input().split()))
    sala.append(linha)

maior_distancia = 0

for i in range(m):
    dist_minima = n
    cadeiras = sala[i]

    for j in range(n):
        if cadeiras[j] == 1:
            dist_minima = min(dist_minima, j)

    maior_distancia = max(maior_distancia, dist_minima)

print(maior_distancia)