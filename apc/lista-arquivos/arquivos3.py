def concat(s):
    fin = open(s, 'r')
    linhas = fin.readlines()
    concatenado = ''.join(linhas).replace('\n', ' ')
    print(concatenado)

arquivo = input()
concat(arquivo)