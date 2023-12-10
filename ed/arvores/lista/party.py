""" 
    Para resolver esse problema, precisamos ver qual arvore e a mais alta, em outras palavras, a arvore
    hierarquica com o maior numero de camadas. Com isso, achamos o numero minimo de grupos que podemos formar
    na festa, visto que qualquer numero menor resultaria em um funcionario estando no mesmo grupo com um superior
    (imediato ou nao) o que nao e permitido.
 """

import sys
sys.setrecursionlimit(10**4)
    
class Arvore:
    def __init__(self) -> None:
        self.nos = {}
 
    def put_edge(self, u, v) -> None:
        if u not in self.nos:
            self.nos[u] = []
 
        if v not in self.nos:
            self.nos[v] = []
 
        self.nos[u].append(v)
 
    def put_vertex(self, u):
        if u in self.nos: return
 
        self.nos[u] = []
 
    def get_filhos(self, u):
        return self.nos[u]
    
    def get_raiz(self) -> int:
        return self.raiz

def dfs(atual):
    # caso chegamos em um folha
    if chefes.get_filhos(atual) == []: return 0
 
    # altura da arvore
    h = 0

    # analisando cada filho do no atual
    for prox in chefes.get_filhos(atual):
        # altura do no atual = 1 + altura de sua subarvore mais alta
        h = max(h, 1 + dfs(prox))

    return h
 
n = int(input())
chefes = Arvore()

# montar a arvore
for funcionario in range(1,n+1):
    chefe = int(input())
 
    if chefe == -1:
        chefes.put_vertex(funcionario)
 
    # aresta: chefe -> funcionario
    chefes.put_edge(chefe, funcionario)
 
# resposta = arvore mais alta 
ans = 0

# para cada funcionario, verificamos sua altura caso
# ele fosse a raiz de sua propria arvore. Com isso, 
# para cada iteracao, guardamos o maior valor calculado
# ate agora
for i in range(1,n+1):
    ans = max(ans, dfs(i))
 
print(ans+1)