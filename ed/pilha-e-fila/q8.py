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

N, F, P = map(int, input().split())
pesos = list(map(int, input().split()))

tempo_total = 0
fila = Queue()

for i in range(N):
    peso = pesos[i]
    
    if peso <= P:
        tempo_total += 5
    else:
        tempo_total += 10
        peso -= 2
    
    fila.enqueue(peso)
    
    if i % F == F - 1 or i == N - 1:
        while fila and fila[0] <= P:
            fila.dequeue()
            tempo_total += 5

print(tempo_total)
