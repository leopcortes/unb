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

while True:
    N, K = map(int, input().split())
    
    if N == 0 and K == 0:
        break
    
    chegada_saida = []
    for _ in range(N):
        chegada, saida = map(int, input().split())
        chegada_saida.append((chegada, saida))
        
    pilha = Stack()
    possivel = True
    ultima_saida = 0
        
    for i in range(N):
        while not pilha.isEmpty() and pilha.peek() <= chegada_saida[i][0]:
            pilha.pop()

        if pilha.size() < K:
            pilha.push(chegada_saida[i][1])
        else:
            possivel = False
            break
        
        if i < N - 1 and pilha.peek() > chegada_saida[i + 1][0]:
            possible = False
            break

    if possivel:
        print("Sim")
    else:
        print("Nao")
    
    