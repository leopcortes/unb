def mediana_e_mais_proximo_media_e_pos(lista):
    lista_ordenada = sorted(lista)
    tam = len(lista_ordenada)
    if tam > 0:
        if tam % 2 == 0:
            mediana = (lista_ordenada[int(tam/2)] + lista_ordenada[int(tam/2-1)])/2
        else:
            mediana = lista_ordenada[int(tam/2)]
        soma = sum(lista_ordenada)
        media = soma / tam
        diferenca_minima = float('inf')
        valor_proximo = lista_ordenada[0]
        indice_proximo = 0
        for i in range(tam):
            diferenca = abs(media - lista_ordenada[i])
            if diferenca < diferenca_minima:
                diferenca_minima = diferenca
                valor_proximo = lista_ordenada[i]
                indice_proximo = i
    else:
        mediana = None
        valor_proximo = None
        indice_proximo = None
    return [mediana, valor_proximo, indice_proximo]


lista = [1, 2, 3, 4]
print(mediana_e_mais_proximo_media_e_pos(lista))

lista = [1, 1, 1, 1, 1, 1, 1, 50, 43, 0]
print(mediana_e_mais_proximo_media_e_pos(lista))

lista = []
print(mediana_e_mais_proximo_media_e_pos(lista))