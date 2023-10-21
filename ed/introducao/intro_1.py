def divisores(n):
    lista = []
    for i in range(1, n + 1):
        if n % i == 0:
            lista.append(i)
            
    return lista

print(divisores(5))
print(divisores(120))
print(divisores(131))