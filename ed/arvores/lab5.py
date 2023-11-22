class ArvoreBinaria():
    def __init__(self, dado, esq=None, dir=None):
        self.dado = dado
        self.esq = esq
        self.dir = dir

def verificaSimetria(raiz):
    def simetricas(esquerda, direita):
        if not esquerda and not direita:
            return True
        elif not esquerda or not direita:
            return False
        else:
            return (esquerda.dado == direita.dado) and simetricas(esquerda.dir, direita.esq) and simetricas(esquerda.esq, direita.dir)
    if not raiz:
        return True
    return simetricas(raiz.esq, raiz.dir)

raiz1 = ArvoreBinaria(1, ArvoreBinaria(0, ArvoreBinaria(0), ArvoreBinaria(1)), ArvoreBinaria(0, ArvoreBinaria(1), ArvoreBinaria(0)))
print(verificaSimetria(raiz1))

raiz2 = ArvoreBinaria(1, ArvoreBinaria(0, ArvoreBinaria(0), ArvoreBinaria(1)), ArvoreBinaria(0, ArvoreBinaria(0), ArvoreBinaria(1)))
print(verificaSimetria(raiz2))

raiz3 = ArvoreBinaria(0, ArvoreBinaria(1, ArvoreBinaria(1, None, None), ArvoreBinaria(0, None, None)), ArvoreBinaria(1, ArvoreBinaria(1, None, None), ArvoreBinaria(0, None, None)))
print(verificaSimetria(raiz3))