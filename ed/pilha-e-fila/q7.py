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
roupas_na_cadeira = Stack()
total_roupas = 0
total_tempo = 0

for _ in range(N):
    entrada = input().split()
    tempo = int(entrada[2])
    
    roupas_na_cadeira.push(entrada[:2])
    
    total_roupas += 1
    total_tempo += tempo

while not roupas_na_cadeira.isEmpty():
    roupa = roupas_na_cadeira.pop()
    tipo = roupa[0]
    cor = roupa[1]
    print(f"Tipo: {tipo}, Cor: {cor}")

print(f"Total de roupas: {total_roupas}")
print(f"Total de tempo: {total_tempo}")
