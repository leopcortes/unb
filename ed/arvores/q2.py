class ArvoreBinaria():
    def __init__(self, dado, esq=None, dir=None):
        self.dado = dado
        self.esq = esq
        self.dir = dir

def constituiArvoreBinariaDeBusca(raiz, min_val=float('-inf'), max_val=float('inf')):
    if raiz is None:
        return True

    if not (min_val < raiz.dado < max_val):
        return False

    return (constituiArvoreBinariaDeBusca(raiz.esq, min_val, raiz.dado) and constituiArvoreBinariaDeBusca(raiz.dir, raiz.dado, max_val))

# Exemplo de uso:
raiz1 = ArvoreBinaria(10, ArvoreBinaria(8), ArvoreBinaria(28, ArvoreBinaria(26), ArvoreBinaria(30)))
raiz2 = ArvoreBinaria(10, ArvoreBinaria(5), ArvoreBinaria(15, ArvoreBinaria(11), ArvoreBinaria(20)))
raiz3 = ArvoreBinaria(7, ArvoreBinaria(4), ArvoreBinaria(10, ArvoreBinaria(11), ArvoreBinaria(15))) 

print(constituiArvoreBinariaDeBusca(raiz1))
print(constituiArvoreBinariaDeBusca(raiz2))
print(constituiArvoreBinariaDeBusca(raiz3))
