def erase(lista):
    return [tupla for tupla in lista if len(tupla) > 0]

l = [(), (15,), (), (), (2, 15, 17)]
resposta = erase(l)
print(resposta)