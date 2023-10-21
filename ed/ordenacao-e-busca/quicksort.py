def quickSort(alist):
    if len(alist) <=1:
        return alist
    esquerda, pivo, direita = reordena(alist)
    esquerda = quickSort(esquerda)
    direita = quickSort(direita)
    esquerda.append(pivo)
    esquerda.extend(direita)
    return esquerda

def reordena(alist):
    if len(alist) <=1:
        return [], alist[0], []
    pivo = alist[0]
    esquerda, direita = [], []
    
    for i in alist[1:]:
        if i <= pivo:
            esquerda.append(i)
        elif i > pivo:
            direita.append(i)

    return esquerda, pivo, direita


print(quickSort([3,4,6,1,2,5]))
print(quickSort([3,4,6,1,2,6,5]))