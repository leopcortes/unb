""" 
    Se analisarmos bem o problema, podemos ver que se trata de uma arvore binaria de decisao: ou voce multiplica o
    numero por 2 ou subtrai 1 do numero. Como queremos a quantidade minima de vezes que apertamos o botao, queremos
    encontrar o resultado 'm' que aparece primeiro, isto e, esta em um nivel/altura menor na arvore binaria. Podemos 
    encontra-lo usando o algoritmo de BFS (Breadth First Search ou Busca em Largura).
 """

class Fila:
    def __init__(self) -> None:
        self.items = []
 
    def enqueue(self, item):
        self.items.append(item)
 
    def dequeue(self):
        self.items.pop(0)
 
    def front(self):
        return self.items[0]
    
    def size(self):
        return len(self.items)
    
    def is_empty(self):
        return self.size() == 0
    
# tamanho maximo do vetor "vis"    
MAX = 10**4 +3
# vetor vis: o indice i indica que se o numero i ja foi visto ou nao na BFS
vis = [0]*MAX
def bfs(inicio, destino):
    fila = Fila()
    fila.enqueue((inicio,0))
    while not fila.is_empty():
        # fila: (numero atual, vezes clicadas ate agora)
        atual, ops = map(int, fila.front())
        fila.dequeue()
 
        # se o numero esta fora do intervalo ou ja foi visto, o ignoramos
        if atual >= MAX or vis[atual] or atual < 1:        
            continue
        # marcamos o numero atual como visto
        vis[atual] = 1
 
        # verificamos se ja chegamos no numero desejado
        if atual == destino:
            return ops
        
        # adiciona o filho da esquerda = (2*atual)
        fila.enqueue((2*atual, ops+1))
 
        # adiciona o filho da direita = (atual - 1)
        fila.enqueue((atual-1, ops+1))
 
    # retorna -1 se nao for possivel chegar ate o numero (impossivel nessa questao)
    return -1
 
i,d = map(int, input().split())
print(bfs(i,d))
 