def primos_gemeos(n):
    def eh_primo(numero):
        if numero <= 1:
            return False
        if numero == 2:
            return True
        if numero % 2 == 0:
            return False
        for i in range(3, int(numero ** 0.5) + 1, 2):
            if numero % i == 0:
                return False
        return True

    pares_gemeos = []
    numero = 2
    while len(pares_gemeos) < n:
        if eh_primo(numero) and eh_primo(numero + 2):
            pares_gemeos.append((numero, numero + 2))
        numero += 1

    return pares_gemeos

n = int(input())
resultado = primos_gemeos(n)
print(resultado)