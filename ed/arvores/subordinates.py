""" 
    Para descobrirmos a quantidade de de subordinados que cada empregado tem na empresa, basta
    calcularmos quantas folhas cada vertice da arvore tem. A folhas, nesse contexto, sao os empregados
    sem subordinados/funcionario abaixo dele na hierarquia da empresa.
 """

import sys
sys.setrecursionlimit(10**6)
    
class Arvore:
    def __init__(self, n) -> None:
        self.nos = {}
    
    def put_edge(self, u, v) -> None:
        if u not in self.nos:
            self.nos[u] = []
 
        if v not in self.nos:
            self.nos[v] = []
 
        self.nos[u].append(v)
 
    def get_filhos(self,u):
        return self.nos[u]
 
def dfs(atual):
    # se chegamos em um folha (funcionario sem empregados)
    if arvore.get_filhos(atual) == []: return 0
 
    # subordinados total
    subs = 0

    # para cada empregado do funcionario atual, chamamos a funcao novamente
    for emp in arvore.get_filhos(atual):
        subs += 1 + dfs(emp)
 
    # definimos a quantidade total de empregados que o
    # funcionario atual tem
    ans[atual] = subs

    # retornamos esse total
    return subs
 
n = int(input())
arvore = Arvore(n)
 
chefes = [int(x) for x in input().split()]
 
empregado = 2
for chefe in chefes:
    # adicionamos uma aresta: chefe -> empregrado
    arvore.put_edge(chefe, empregado)
    empregado += 1

# vetor onde o indice i corresponde ao i-esimo empregado e 
# ans[i] a quantidade de empregados que o empregado i tem 
ans = [0] * (n+1)

# chama a dfs comecando do funcionario 1 (diretor geral)
ans[1] = dfs(1)
 
for i in range(1, n+1):
    print(ans[i], end=' ')
print()