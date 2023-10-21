usuarios = int(input("Quantos usuarios (1 a 4): "))
dist = int(input("Distancia a ser percorrida (em KMs): "))
taxa = float(input("Digite a taxa do banco (entre 0 e 1): "))

print(f"O preco final da viagem e: {((10*dist)/usuarios + usuarios*4) + taxa * ((10*dist)/usuarios + usuarios*4):.2f}")