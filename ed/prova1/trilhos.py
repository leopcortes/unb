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

while True:
    N = int(input())
    if N == 0:
        break

    while True:
        train_order = list(map(int, input().split()))
        train_order = ''.join(map(str, train_order))
        
        if train_order[0] == "0":
            print()
            break
        
        deque1 = Deque()
        deque2 = Deque()
        is_palindrome = True

        for wagon in train_order:
            deque1.addRear(wagon)
            deque2.addFront(wagon)

        while deque1.size() > 1:
            front_wagon = deque1.removeFront()
            rear_wagon = deque2.removeRear()

            if front_wagon != rear_wagon:
                is_palindrome = False
                break

        if is_palindrome:
            print("Yes")
        else:
            print("No")
            
