"""
Ajude a escrever funções para o Jogo da Velha. Neste exercício, o jogo sempre começará 
com o jogador (X) e ambos os jogadores devem efetuar seus lances de forma alternada. 
Após cada lance, o tabuleiro deve ser atualizado. Ajude a construir esse jogo 
implementando somente a seguinte função:
''' Funcao que testa se a partida terminou '''
def jogoTerminou(matriz):

Entrada:
A função jogoTerminou possui como parâmetro uma matriz de caracteres representando o 
tabuleiro e suas jogadas. Cada posição da matriz inicial é dada por pela sequência 
de três caracteres { '-' , 'X' , 'O'}, sendo que '-' é um espaço em branco).

Saída:
A função deve retornar o estado de checagem do tabuleiro sendo 0, caso a partida não 
tenha terminado, 1 caso a haja um vencedor (independente de quem) e 2 caso a partida 
tenha terminado em empate.

"""

def jogoTerminou(matriz):
    # Linhas
    for linha in matriz:
        if linha[0] == linha[1] and linha[0] == linha[2] and linha[0] != " - ":
            return 1

    # Colunas
    for coluna in range(3):
        if matriz[0][coluna] == matriz[1][coluna] and matriz[0][coluna] == matriz[2][coluna] and matriz[0][coluna] != " - ":
            return 1
        
    # Diagonais
    if matriz[0][0] == matriz[1][1] and matriz[0][0] == matriz[2][2] and matriz[0][0] != " - ":
        return 1
    if matriz[0][2] == matriz[1][1] and matriz[0][2] == matriz[2][0] and matriz[0][2] != " - ":
        return 1
    
    # Não terminou
    for i in range(3):
        for j in range(3):
            if matriz[i][j] == " - ":
                return 0
            
    # Empate
    return 2

matriz1 = [[" X ", " - ", " X "],
           [" - ", " O ", " O "],
           [" O ", " - ", " X "]]

matriz2 = [[" X ", " X ", " X "],
           [" - ", " O ", " O "],
           [" O ", " - ", " X "]]

matriz3 = [[" X ", " O ", " X "],
           [" X ", " O ", " O "],
           [" O ", " X ", " X "]]

print(f"Resultado Matriz 1 = {jogoTerminou(matriz1)}")
print(f"Resultado Matriz 2 = {jogoTerminou(matriz2)}")
print(f"Resultado Matriz 3 = {jogoTerminou(matriz3)}")