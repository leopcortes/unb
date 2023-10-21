class Queue:
    def __init__(self):
        self.items = []
    
    def isEmpty(self):
        return self.items == []
    
    def enqueue(self, item):
        self.items.insert(0, item)
    
    def dequeue(self):
        return self.items.pop()
    
    def size(self):
        return len(self.items)

def eternidade_na_fila(fila):
    primeiro = fila.dequeue()
    fila.enqueue(primeiro)
    return fila

nomes = input().split()
X = int(input())

fila = Queue()

for nome in nomes:
    fila.enqueue(nome)

for _ in range(X):
    fila = eternidade_na_fila(fila)

print(f'Pessoa da frente: {fila.items[-1]}')
print(f'Pessoa do fim: {fila.items[0]}')
