def corrida(a, b, c):
    if a > 0:
        if b == 0:
            print(f"Faltam {a} voltas, hora de trocar os pneus.")
            b = c
        corrida(a-1, b-1, c)
    else:
        print("A corrida chegou ao fim.")

corrida(30, 5, 5)
corrida(8,10,10)
corrida(10,8,8)