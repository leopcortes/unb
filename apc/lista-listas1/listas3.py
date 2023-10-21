sequencia = list(map(int, input().split()))
n = int(input())

multiplos = []

for numero in sequencia:
    if numero % n == 0:
        multiplos.append(numero)

print(' '.join(map(str, multiplos)))