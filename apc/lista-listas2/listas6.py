N, M, f = map(int, input().split())

matriz = []
for _ in range(N):
    valores = input().split()
    matriz.append(valores)
    
Nf = N // f
Mf = M // f

nova_matriz = []
for i in range(0, N, f):
    for j in range(0, M, f):
        quadrante = []
        for x in range(f):
            for y in range(f):
                quadrante.append(matriz[i+x][j+y])
        novo_valor = max(quadrante)
        nova_matriz.append(novo_valor)

for i in range(0, Nf * Mf, Mf):
    linha = nova_matriz[i:i+Mf]
    print(' '.join(map(str, linha)))