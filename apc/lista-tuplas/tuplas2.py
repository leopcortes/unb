def convert(list):
    dicio = {}
    for chave, valor in list:
        if chave in dicio:
            dicio[chave].append(valor)
        else:
            dicio[chave] = [valor]
    return dicio 
    
l = [(3, 91), (4, 69), (1, 85), (1, 96), (1, 7), (4, 94)]
resposta = convert(l)
print(resposta)