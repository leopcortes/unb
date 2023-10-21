lista = []
aux = True
while aux:
    entrada = input()
    entrada = entrada.split(' ')
    instrucao = entrada[0]
    if len(entrada) > 1:
        valor = int(entrada[1])
    
    if(instrucao == "I"):
        lista.insert(0, valor)    
    elif(instrucao == "F"):
        lista.append(valor)
    elif(instrucao == "P"):
        removido = lista.pop()
        print(removido)
    elif(instrucao == "D"):
        removido = lista.pop(0)
        print(removido)
    elif(instrucao == "X"):
        for i in range(len(lista)):
            print(lista[i])
        aux = False