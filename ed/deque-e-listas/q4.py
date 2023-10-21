class Deque:
	def __init__(self):
		self.items = []
	
	def isEmpty(self):
		return self.items == []
	
	def addFront(self, item):
		self.items.append(item)
	
	def addRear(self, item):
		self.items.insert(0,item)
	
	def removeFront(self):
		return self.items.pop()
	
	def removeRear(self):
		return self.items.pop(0)
	
	def size(self):
		return len(self.items)

d = Deque()
list = []
entrada = input()

for char in entrada:
    if char in "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ .,><;:~^/\|":
        d.addFront(char)
    elif char in "0123456789":
        d.addRear(char)
    elif char == "*":
        a = d.removeFront()
        list.append(a)
    elif char == "+":
        b = d.removeRear()
        list.append(b)
   
print(''.join(list))