def min_max(t):
  return min(t), max(t)

list = [1,2,3,4,5,6,7,8,9,10]
print(min_max(list))

def printall(*args):
  print(args)

printall(1, 2.0, '3')

s = 'abc'
t = [0, 1, 2]
zip(s, t)

for pair in zip(s, t):
	print(pair)
 
d = {'a':0, 'b':1, 'c':2}
t = d.items()
print(t)

print(tuple("Ola mundo"))
