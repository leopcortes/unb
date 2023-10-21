numeros = list(map(int, input().split()))
indice_inicio, indice_fim = map(int, input().split())

lista_cortada = numeros[indice_inicio:indice_fim]

print(lista_cortada)
