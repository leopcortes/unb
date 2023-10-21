def frequencia(msg):
    cont = {}
    char_mais_frequente = ""
    freq_max = 0
    
    for char in msg:
        if char in cont:
            cont[char] += 1
        else:
            cont[char] = 1

    for char, frequencia in cont.items():
        if frequencia > freq_max:
            char_mais_frequente = char
            freq_max = frequencia

    return char_mais_frequente

print(frequencia('Estrutura de Dados'))
print(frequencia('oftalmotorrinolaringologista'))
print(frequencia('1*22*333*4444*55555'))