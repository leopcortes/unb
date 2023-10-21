def decifrar():
    N = int(input())

    mapa = []
    for i in range(N):
        valores = input().split()
        mapa.append(valores)

    contX = 0
    achou = "O one piece eh real!"
    nao_achou = "Talvez o tesouro seja os amigos que fizemos no caminho"
    for j in range(N):
        for k in range(N):
            if j == k or j + k == N-1:
                if mapa[j][k] != 'X':
                    return nao_achou
                contX += 1
            elif mapa[j][k] == 'X':
                return nao_achou
        
        if contX != 2:
            return nao_achou
        
        return achou

print(decifrar())