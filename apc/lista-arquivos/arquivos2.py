import csv

def lerArquivoCSV(nome_arquivo):
    fin = open(nome_arquivo, 'r')
    leitor = csv.reader(fin)
    for linha in leitor:
        ultimo_elemento = linha[-1]
        print(ultimo_elemento)

arquivo = input()
lerArquivoCSV(arquivo)