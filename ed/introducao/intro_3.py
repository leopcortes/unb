def lesma_mais_veloz(velocidades):
    c1_mais_veloz = 0
    c2_mais_veloz = 0
    c3_mais_veloz = 0

    for velocidade in velocidades:
        if velocidade < 10:
            if velocidade > c1_mais_veloz:
                c1_mais_veloz = velocidade
        elif velocidade < 20:
            if velocidade > c2_mais_veloz:
                c2_mais_veloz = velocidade
        else:
            if velocidade > c3_mais_veloz:
                c3_mais_veloz = velocidade

    return c1_mais_veloz, c2_mais_veloz, c3_mais_veloz

L = int(input())

velocidades = []

for _ in range(L):
    velocidade = int(input())
    velocidades.append(velocidade)

lesma_c1, lesma_c2, lesma_c3 = lesma_mais_veloz(velocidades)

print(lesma_c1, lesma_c2, lesma_c3)