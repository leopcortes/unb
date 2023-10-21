def soma_adinilson(lista):
    resultado = 0
    multiplicador = 2

    for i in range(len(lista)):
        resultado += lista[i] * multiplicador
        multiplicador *= 0.5

    return resultado


# Leitura da lista de inteiros
entrada = input().split()
lista = [int(num) for num in entrada]

# Chamada da função soma_adinilson
resultado = soma_adinilson(lista)

# Exibição do resultado com duas casas decimais
print(f"{resultado:.2f}")
