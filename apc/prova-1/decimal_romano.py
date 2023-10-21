def decimal_romano(decimal):
    valores =  [1000, 900, 500,  400, 100,   90,  50,   40,  10,    9,   5,    4,   1] # Valores em decimal
    simbolos = ['M', 'CM', 'D', 'CD', 'C', 'XC', 'L', 'XL', 'X', 'IX', 'V', 'IV', 'I'] # Valores em romano
    romano = '' # String onde sera armazenado o numero em romano
    
    for i in range(len(valores)): # Para cada valor em decimal em ordem decrescente
        while decimal >= valores[i]: # Enquanto o numero de entrada for maior ou igual o valor atual
            romano += simbolos[i] # Adiciona o simbolo romano correspondente
            decimal -= valores[i] # Diminui o valor correspondente no valor de entrada
    
    return romano # Retorna a string com o o numero em romano

decimais = [10, 26, 99, 149, 349, 444, 666, 784, 1679, 2022, 2023, 10000] # Valores a serem convertidos
for i in decimais: # Para cada valor
    print(f"Decimal: '{i:5d}' --- Romano: '{decimal_romano(i)}'") # Imprime o numero em decimal e em romano