def codigo_gray(n):
    return n ^ (n >> 1)  # Deslocamento a direita fazendo XOR com o número original
 
n = int(input()) # Entrada do usuário

print(f"{codigo_gray(n):016b}") # Impressão em 16 caractéres do número em binário na forma de código de gray