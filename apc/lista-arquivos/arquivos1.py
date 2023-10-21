def aprendendoArquivos(s):
    fin = open(s, 'r')
    primeira_linha = fin.readline().strip()
    if primeira_linha.isdigit():
        print("42 eh a resposta para tudo!")
    else:
        print("Ola", primeira_linha + "!")