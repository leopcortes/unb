import csv

nome_arquivo = input()

arquivo = open(nome_arquivo, 'r')
leitor = csv.reader(arquivo)
linhas = list(leitor)

cabecalho = linhas[0]
qnt_fornecedores, qnt_itens = map(int, cabecalho[0].split())
fornecedores = cabecalho[1:]

for i in range(1, qnt_itens+1):
    item = linhas[i][0]
    precos = list(map(float, linhas[i][1:]))
    indice_menor_preco = precos.index(min(precos))
    melhor_fornecedor = fornecedores[indice_menor_preco]
    print(item, melhor_fornecedor)