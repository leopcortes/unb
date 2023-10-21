class Stack:
	def __init__(self):
		self.items = []
	
	def isEmpty(self):
		return self.items == []
	
	def push(self, item):
		self.items.append(item)
	
	def pop(self):
		return self.items.pop()
	
	def peek(self):
		return self.items[len(self.items)-1]
	
	def size(self):
		return len(self.items)

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

class PriorityQueue:
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




N = int(input())
for _ in range(N):
    
	pilha = Stack()
	fila = Queue()
	fila_prioridade = Queue()

	M = int(input())
	for _ in range(M):
		inst, val = input().split()
		val = int(val)

		if inst == "in":
			pilha.push(val)
			fila.enqueue(val)
			fila_prioridade.enqueue(val)
   
			primeiro_pilha = val
			primeiro_fila = val
			primeiro_fila_prioridade = val

		else:
			ultimo_pilha = pilha.pop()
			ultimo_fila = fila.dequeue()