lista1 = []
lista2 = []
medias = []

for _ in range(5):
    num = int(input())
    lista1.append(num)

for _ in range(5):
    num = int(input())
    lista2.append(num)
    
tuplas = list(zip(lista1, lista2))

for i in tuplas:
    media = sum(i)/len(i)
    medias.append(media)
    
print(tuplas)
print(medias)