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

N = int(input())
pilha = Stack()

for _ in range(N):
    num = int(input())
    
    if num != 0:
        pilha.push(num)
    else:
        pilha.pop()
    
soma = 0    
while not pilha.isEmpty():
    soma += pilha.pop()
    
print(soma)