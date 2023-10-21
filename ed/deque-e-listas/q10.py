from collections import deque

n = int(input())
lista = list(map(int, input().split()))
k = int(input())

resultado = []
d = deque()

for i in range(k):
    while d and lista[i] >= lista[d[-1]]:
        d.pop()
    d.append(i)

for i in range(k, n):
    resultado.append(lista[d[0]])

    while d and d[0] <= i-k:
        d.popleft()

    while d and lista[i] >= lista[d[-1]]:
        d.pop()

    d.append(i)

resultado.append(lista[d[0]])
print("  ".join(map(str, resultado)))