def stockmarket(lista_tuplas):
    dicionario = {}
    for data, preco, quantidade, simbolos in lista_tuplas:
        total = preco * quantidade
        total = float(total)
        if data in dicionario:
            dicionario[data] += total
        else:
            dicionario[data] = total
    return dicionario

stock = [('25-Out-2020', 40.0, 100, 'GM'),
('25-Out-2020', 42.0, 100, 'FIT'),
('01-Nov-2020', 36, 100, 'GM'),
('01-Nov-2020', 20, 100, 'FIT')]
print(stockmarket(stock))