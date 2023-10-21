m, n = map(int, input().split())
sequencia = list(map(int, input().split()))

soma = sum(sequencia[:n])
print(soma // n)

for i in range(n, m):
    soma = soma - sequencia[i - n] + sequencia[i]
    print(soma // n)