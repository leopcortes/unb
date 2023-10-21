def simples(a):
    a = input()
    if a == "repete":
        print("Olá! Vamos repetir!")
        simples(a)
    
a = input()
if a == "repete":
    print("Olá! Vamos repetir!")
    simples(a)