def imprimeTermos(n):
    if n > 0: 
        print(n)
        imprimeTermos(n-2)
    else: 
        print(0)
    
imprimeTermos(11)