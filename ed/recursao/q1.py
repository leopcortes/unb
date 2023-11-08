def fibonacci(n, cont=None):
    if cont is None:
        cont = [0] * (n+1)
    
    cont[n] += 1

    if n <= 1:
        return n
    else:
        return fibonacci(n-1, cont) + fibonacci(n-2, cont)

n = int(input())
cont = [0] * (n+1)
res = fibonacci(n, cont)

print(f'fibonacci({n}) = {res}.')
for i in range(n+1):
    print(f'{cont[i]} chamada(s) a fibonacci({i}).')