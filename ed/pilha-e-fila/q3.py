class Stack:
    def __init__(self):
        self.items = []

    def isEmpty(self):
        return self.items == []

    def push(self, item):
        self.items.insert(0, item)

    def pop(self):
        return self.items.pop(0)

    def peek(self):
        return self.items[0]

    def size(self):
        return len(self.items)

entrada = input()
pilha = Stack()
resultado = ""

for char in entrada:
    if char != "*":
        pilha.push(char)
    elif char == "*":
        if not pilha.isEmpty():
            resultado += pilha.pop()
            
print(resultado)
