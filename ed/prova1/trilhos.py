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
    
class Queue():
    def __init__(self):
        self.items = []

    def enqueue(self,item):
        self.items.insert(0, item)

    def dequeue(self):
        self.items.pop()

    def size(self):
        return len(self.items)
    
    def isEmpty(self):
        return self.size() == 0
    
    def front(self):
        return self.items[self.size()-1]
    
n = int(input())
while n != 0:
    # le a permutacao desejada
    permutacao = [int(x) for x in input().split()]

    while permutacao != [0]:
        fila, pilha = Queue(), Stack()
        ans = []

        # poe os vagoes na fila
        for vagao in range(1, n+1):
            fila.enqueue(vagao)

        for pi in permutacao:
            # ver se o vagao nao esta na pilha
            if not pilha.isEmpty() and pilha.peek() == pi:
                ans.append(pilha.peek())
                pilha.pop()
                continue

            # colocar os vagoes na pilha ate achar o vagao desejado
            while not fila.isEmpty() and fila.front() != pi:
                pilha.push(fila.front())
                fila.dequeue()

            # achou o vagao
            if not fila.isEmpty():
                ans.append(fila.front())
                fila.dequeue()

            # n e possivel fazer a permutacao
            else:
                break

        if ans == permutacao: print("Yes")
        else: print("No")

        permutacao = [int(x) for x in input().split()]

    print()

    n = int(input())