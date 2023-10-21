N, M, K = map(int, input().split())
produtos = list(map(int, input().split()))
precos = []

for _ in range(N):
    precos.extend(list(map(int, input().split())))

precos.sort()

compras = 0
for preco in precos:
    if M < preco:
        break
    M -= preco
    compras += 1
    if compras % K == 0:
        compras = 0

if compras == 0:
    print("Sim")
else:
    print("Nao")