def wally(nome_arquivo):
    arquivo = open(nome_arquivo, 'r')
    linhas = arquivo.readlines()
    
    for i, linha in enumerate(linhas):
        if 'wally' in linha:
            linha_inicial = i+1
            coluna_inicial = linha.index('wally')+1
            print(f"{linha_inicial} {coluna_inicial} horizontal")
            return
    
    num_colunas = len(linhas[0])-1
    num_linhas = len(linhas)
    for coluna in range(num_colunas):
        for linha in range(num_linhas - 4):
            if (linhas[linha+0][coluna] == 'w' and linhas[linha+1][coluna] == 'a' and linhas[linha+2][coluna] == 'l' and linhas[linha+3][coluna] == 'l' and linhas[linha+4][coluna] == 'y'):
                linha_inicial = linha+1
                coluna_inicial = coluna+1
                print(f"{linha_inicial} {coluna_inicial} vertical")
                return

nome_arquivo = input()
wally(nome_arquivo)