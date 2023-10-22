class ElementoFila():
    def __init__(self, valorInicial=0, prioridadeInicial=0):
        self.valor = valorInicial
        self.prioridade = prioridadeInicial
        self.elementoAnteriorNaFila = None

class FilaDePrioridade():
    def __init__(self):
        self.inicioFila = None
        self.fimFila = None

    def enfileirar(self, valor, prioridade):
        novo_elemento = ElementoFila(valor, prioridade)
        if self.inicioFila is None:
            self.inicioFila = novo_elemento
            self.fimFila = novo_elemento
        else:
            if novo_elemento.prioridade > self.inicioFila.prioridade:
                novo_elemento.elementoAnteriorNaFila = self.inicioFila
                self.inicioFila = novo_elemento
            else:
                elemento_atual = self.inicioFila
                while elemento_atual.elementoAnteriorNaFila is not None and elemento_atual.elementoAnteriorNaFila.prioridade >= novo_elemento.prioridade:
                    elemento_atual = elemento_atual.elementoAnteriorNaFila
                novo_elemento.elementoAnteriorNaFila = elemento_atual.elementoAnteriorNaFila
                elemento_atual.elementoAnteriorNaFila = novo_elemento

    def desenfileirar(self):
        if self.inicioFila is None:
            return None
        elemento_retirado = self.inicioFila
        self.inicioFila = self.inicioFila.elementoAnteriorNaFila
        return elemento_retirado.valor

fila_prioridade = FilaDePrioridade()
fila_prioridade.enfileirar("Item 1", 2)
fila_prioridade.enfileirar("Item 2", 1)
fila_prioridade.enfileirar("Item 3", 3)

while fila_prioridade.inicioFila is not None:
    print(fila_prioridade.desenfileirar())
