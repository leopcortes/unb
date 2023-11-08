class ArvoreBinaria():
    def __init__(self, dado, esq=None, dir=None):
        self.dado = dado
        self.esq = esq
        self.dir = dir

def verificaSimetria(raiz):
    def saoSubArvoresSimetricas(esq, dir):
        if esq is None and dir is None:
            return True

        if esq is None or dir is None:
            return False

        return (esq.dado == dir.dado and
                saoSubArvoresSimetricas(esq.esq, dir.dir) and
                saoSubArvoresSimetricas(esq.dir, dir.esq))

    return saoSubArvoresSimetricas(raiz.esq, raiz.dir)

raiz1 = ArvoreBinaria(1, ArvoreBinaria(0, ArvoreBinaria(1), ArvoreBinaria(0)), ArvoreBinaria(0, ArvoreBinaria(0), ArvoreBinaria(1)))
raiz2 = ArvoreBinaria(1, ArvoreBinaria(0, ArvoreBinaria(0), ArvoreBinaria(1)), ArvoreBinaria(0, ArvoreBinaria(0), ArvoreBinaria(1)))

print(verificaSimetria(raiz1))
print(verificaSimetria(raiz2))
