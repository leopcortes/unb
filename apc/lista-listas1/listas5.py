def paron(palavras):
    def count_vogais(palavra):
        vogais = 'aeiouAEIOU'
        count = 0
        for letra in palavra:
            if letra in vogais:
                count += 1
        return count

    palavras_pares = []
    for palavra in palavras:
        if count_vogais(palavra) % 2 == 0:
            palavras_pares.append(palavra)

    return palavras_pares


print(paron(['palavra', 'escrever', 'detesta', 'lista', 'todas']))
print(paron(['todos', 'nos', 'adoramos', 'disciplina', 'apc']))
print(paron([]))