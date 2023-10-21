def triangulo(x, size):
    if size > 0:
        triangulo(x+1, size-2)
        print(' '*x + '+'*size)

triangulo(0, 5)
triangulo(3, 7)
triangulo(6, 5)