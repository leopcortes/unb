n = int(input())
pretendentes = []

for _ in range(n):
    nome, sobrenome, altura, massa = input().split()
    altura = int(altura)
    massa = int(massa)
    pretendentes.append((sobrenome, nome, altura, massa))

pretendentes.sort(key=lambda x: (abs(x[2] - 180), abs(x[3]-75) > 0, x[3], x[0], x[1]))

for sobrenome, nome, _, _ in pretendentes:
    print(f"{sobrenome}, {nome}")
