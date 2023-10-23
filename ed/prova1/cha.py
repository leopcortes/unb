class Queue:
    def __init__(self):
        self.items = []

    def isEmpty(self):
        return self.items == []

    def enqueue(self, item):
        self.items.insert(0,item)

    def dequeue(self):
        return self.items.pop()

    def size(self):
        return len(self.items)

    def front(self):
        return self.items[self.size()-1]
    
t = int(input())

for _ in range(t):
    n = int(input())
    
    fila = Queue()

    for _ in range(n):
        li, ri = map(int, input().split())
        fila.enqueue((li,ri))
        
    resposta = []
    tempo = 1
    
    while not fila.isEmpty():
        entrada, saida = fila.front()
        fila.dequeue()
        
        if tempo < entrada:
            tempo = entrada
        
        if tempo > saida:
            resposta.append(0)
        else:
            resposta.append(tempo)
            tempo += 1

    print(*resposta)