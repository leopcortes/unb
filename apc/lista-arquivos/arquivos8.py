import os

frase = input()
nome_arquivo = frase[22:]

if os.path.isfile(nome_arquivo):
    print("da pra abrir")
    arquivo = open(nome_arquivo, 'r')
    tuplas = []
    for linha in arquivo:
        nome, valor = linha.strip().split()
        tupla = (nome, int(valor))
        tuplas.append(tupla)
        
    tuplas_ordenadas = sorted(tuplas, key=lambda x: x[1], reverse=True)
    for tupla in tuplas_ordenadas:
        print(tupla)
else:
    print("nao da pra abrir")