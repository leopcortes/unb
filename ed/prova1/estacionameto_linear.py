class Stack():
    def __init__(self):
        self.items = []

    def push(self,item):
        self.items.append(item)

    def pop(self):
        self.items.pop()

    def size(self):
        return len(self.items)
    
    def isEmpty(self):
        return self.size() == 0
    
    def peek(self):
        return self.items[-1]
    
    
n,k = map(int, input().split())
while n != 0:
    """ 
    A max stack e uma pilha que salva em seu topo o maior elemento de toda a pilha.
    Ela geralmente é feita como uma tupla (xi,mi), onde xi é o i-esimo elemento da pilha e
    mi é o maior elemento da pilha ate a posicao i. Nesse problema, criaremos duas pilhas
    diferentes para melhor visualizacao (uma pilha para o elementos [xi's] e outra para 
    os maiores elementes ate a i-esima posicao [mi's]).
    """

    # pilha para o estacionamento e max stack
    estacionamento, maior_saida = Stack(), Stack()

    # salva os carros do teste
    carros = []
    for _ in range(n):
        ci,si = map(int, input().split())
        carros.append((ci,si))

    ans = True
    tempo = 0
    for carro in carros:
        # carro[0] = tempo de chegada, carro[1] = tempo de saida

        # tempo atual
        tempo = carro[0]

        # eliminando os carros que ja sairam do estacionamento
        while not estacionamento.isEmpty() and estacionamento.peek()[1] <= tempo:
            estacionamento.pop()
            maior_saida.pop()

        # se o estacionamento esta vazio, apenas adicionamos o carro
        if estacionamento.isEmpty():
            estacionamento.push(carro)
            maior_saida.push(carro[1])
            continue

        # se o estacionamento esta lotado ou se o carro atual impossibilita 
        # a saida de algum carro abaixo dele, a resposta e "Nao"
        if estacionamento.size() == k or (estacionamento.peek()[1] < carro[1] or maior_saida.peek() < carro[1]):
            ans = False
            break

        # caso contrario
        else:
            estacionamento.push(carro)

            # recalculamos qual e o novo maior tempo de saida ao adicionarmos o carro atual
            maior_saida.push(max(carro[1], maior_saida.peek()))

    # printa resposta
    if ans: print("Sim")
    else: print("Nao")

    # verifica se ha mais testes
    n,k = map(int, input().split())