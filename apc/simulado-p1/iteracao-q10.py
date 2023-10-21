def ehPrimo(valor):
    for i in range(2, int(valor**(1/2)) + 1):
        if valor % i == 0:
            return 0
    return 1

def divisoresPrimos(n):
    divs = []
    for i in range(1, n):
        if n % i == 0 and ehPrimo(i):
            divs.append(i)
    return divs
    
numeros = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 23, 27, 45, 87, 147, 974, 1279, 4713, 1427689]

for i in numeros:
    if ehPrimo(i) == 1:
        print(f"Numero = {i}, eh primo")
    else:
        print(f"Numero = {i}, nao eh primo")

for i in numeros:
    print(f"Numero = {i}, Divisores primos = {divisoresPrimos(i)}")