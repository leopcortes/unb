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
		return self.items[-1]
	
	def size(self):
		return len(self.items)

pilha = Stack()
total = 0
pesos = Stack()
retirados = 0

while True:
    peso = int(input())
    if peso == 0:
        anilha_desejada = int(input())
        break
    pilha.push(peso)

anilha_atual = pilha.peek()
while True:
    ret = pilha.pop()
    pesos.push(ret)
    retirados += 1
    total += ret
    print(f'Peso retirado: {ret}')
    if anilha_atual == anilha_desejada:
        break
    anilha_atual = pilha.peek()
    
print(f'Anilhas retiradas: {retirados}')
print(f'Peso total movimentado: {total}')
