def controle(n, c):
    if c == n:
        print(f"Parabens Julie! Voce tomou todos os {n} comprimidos!")
        return
    elif c > 0:
        restantes = n - c
        print(f"Voce ja tomou {c} comprimidos, restam {restantes}.")
    controle(n, c + 1)
        
controle(18,0)