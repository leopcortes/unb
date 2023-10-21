import math

def calcular_tempo_restante(bytes_restantes, taxa_transmissao):
    if taxa_transmissao == 0:
        return "pendente"
    return math.ceil(bytes_restantes / taxa_transmissao)

tamanho_arquivo = int(input())
print(f"Transmitindo {tamanho_arquivo} bytes...")

tempo_total = 0
bytes_transmitidos = 0

while bytes_transmitidos < tamanho_arquivo:
    taxa_transmissao = int(input())
    bytes_transmitidos += taxa_transmissao
    tempo_restante = calcular_tempo_restante(tamanho_arquivo - bytes_transmitidos, taxa_transmissao)

    if tempo_total % 5 == 0 or bytes_transmitidos == tamanho_arquivo:
        print(f"Tempo restante: {tempo_restante} segundos.")

    tempo_total += 1

print(f"Tempo total: {tempo_total} segundos.")
