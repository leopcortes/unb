def decodificar_string(comprimida):
    resultado = []
    i = 0
    while i < len(comprimida):
        char = comprimida[i]
        qnt = 0
        i += 1
        while i < len(comprimida) and comprimida[i].isdigit():
            qnt = qnt * 10 + int(comprimida[i])
            i += 1
        resultado.append(char * qnt)
    return ''.join(resultado)

n = int(input())
for _ in range(n):
    string_codificada = input().strip()
    print(decodificar_string(string_codificada))
