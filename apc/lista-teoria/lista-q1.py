valores = [100, 50, 20, 10, 5, 2, 1]
cont100, cont50, cont20, cont10, cont5, cont2, cont1 = 0, 0, 0, 0, 0, 0, 0
conts = [cont100, cont50, cont20, cont10, cont5, cont2, cont1]

valor = 666

for i in range(len(valores)):
    while valor >= valores[i]:
        conts[i] += 1
        valor -= valores[i]
        
for i in range(len(conts)):
    if conts[i] == 0:
        continue
    elif conts[i] == 1:
        print(f"Entregue {conts[i]} nota de R${valores[i]:.2f}".replace('.', ','))
    else:
        print(f"Entregue {conts[i]} notas de R${valores[i]:.2f}".replace('.', ','))