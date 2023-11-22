""" 
    A solução desde problema e percorrer a arvore usando o algoritmo de DFS (Depth First Search ou Busca em Profundidade) verificando se no no atual
    o limite de gatos se excedeu ou nao, caso contrario continuamos ate acharmos um restaurante (uma folha). O problema dessa 
    questao (por estarmos fazendo em Python) e seu limite de memoria, entao se utilizarmos recursao de modo padrao, a questao nao
    passara. Entao, para contornarmos isso, implementaremos nossa propria pilha de recursao usando uma pilha normal, que sera mais
    eficiente que a recursao do Python.
 """

class Stack:
    def __init__(self) -> None:
        self.items = []

    def push(self, item):
        self.items.append(item)

    def pop(self):
        self.items.pop()

    def peek(self):
        return self.items[-1]
    
    def size(self):
        return len(self.items)
    
    def empty(self):
        return self.size() == 0

class Arvore:
    def __init__(self):
        self.nos = {}

        # dicionario que guarda os pais de cada vertice (chave = no : conteudo = pai de u)
        self.pais = {}
    
    def put_edge(self, u, v):
        if u not in self.nos:
            self.nos[u] = []
            
        if v not in self.nos:
            self.nos[v] = []

        self.nos[u].append(v)
    
    def put_vertex(self, u):
        if u not in self.nos:
            self.nos[u] = []

    def get_filhos(self, u):
        if u not in self.nos: 
            return None
        
        return self.nos[u]
    
    # define o pai de u
    def set_pai(self, u, pai):
        self.pais[u] = pai

    # retorna o pai de u
    def get_pai(self, u):
        if u not in self.pais:
            return None
        
        return self.pais[u]

def dfs():
    pilha = Stack()

    # adiciona a pilha a tupla (no inicial, ha ou nao um gato no no inicial)
    pilha.push((1, gatos[1]))

    # quantidade de cafes (restaurantes/folhas alcancaveis)
    cafes = 0

    # simulacao da pilha de recursao
    while not pilha.empty():
        # pilha: (no atual, quantidade de gatos ate agora)
        atual, consec_gatos = pilha.peek()
        pilha.pop()

        # se excedeu a quantidade de gatos
        if consec_gatos > m: continue

        # se chagamos em um folha (em um restaurante)
        if len(arvore.get_filhos(atual)) == 1 and arvore.get_filhos(atual)[0] == arvore.get_pai(atual):
            cafes += 1
            continue

        # analisando cada filho do no atual
        for prox in arvore.get_filhos(atual):
            # definimos o no atual como pai dos filhos do no atual (obviamente)
            if arvore.get_pai(prox) == None:
                arvore.set_pai(prox, atual)

            # evitamos retorna para o no atual, visto que a arvore e bidirecional
            if prox == arvore.get_pai(atual): continue

            # proxima chamada de recursao = adicionar um item na pilha
            pilha.push((prox, (consec_gatos * gatos[prox]) + gatos[prox]))

    return cafes

n, m = map(int, input().split())

# vetor de gatos: o indice i indica se no i-esimo no tem um gato ou n
gatos = [int(x) for x in input().split()]
# torna as consultas indexadas em 1
gatos.insert(0,0)

arvore = Arvore()
for _ in range(n-1):
    u, v = map(int, input().split())
    # aresta: u -> v
    arvore.put_edge(u,v)
    # aresta: v -> u
    arvore.put_edge(v,u)

    # torna a arvore bidirecional

# define o pai da raiz '1' como '-1' (nao tem pai)
arvore.set_pai(1, -1)

ans = dfs()
print(ans)
    