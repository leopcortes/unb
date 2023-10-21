N = int(input())

for _ in range(N):
    expressao = input()
    duplicata = False

    for i in range(len(expressao) - 1):
        if expressao[i] == expressao[i+1] and expressao[i] in "({[" and expressao[i+1] in "({[":
            duplicata = True
            break

    if duplicata:
        print("A expressão possui duplicata.")
    else:
        print("A expressão não possui duplicata.")
