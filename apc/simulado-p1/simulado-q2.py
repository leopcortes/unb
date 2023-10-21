# Na região do Alto Solimões e Vale do Rio Javari, na tríplice fronteira Brasil, Perú e Colômbia vivem os
# Ticunas, maior etnia indígena da Amazônia. Seu o principal item alimentar são os peixes, abundante
# nos rios, igarapés e lagoas da região. Muitos indígenas vivem em comunidades que são distritos do
# município. Abaixo uma visão de um destes distritos, a Comunidade Indígena de Belém do Solimões.

# Nesta comunidade, os indígenas podem ir pescar ou comprar os peixes na taetchica (feira local). Os
# peixes são vendidos em cambadas. Quando os peixes são de espécies pequenas, como o bodó, a cambada
# tem por volta de 20 peixes ou mais. Quando os peixes são grandes, como o pacu, a cambada só tem um
# peixe.

# O preço da cambada varia de acordo com o tipo do peixe, seu tamanho e a quantidade na cambada.
# Para simplificar, vamos supor que em uma cambada de um tipo de peixe, todas as cambadas tem a
# mesma quantidade de peixes e o tamanho de todo peixe de uma espécie é o mesmo

# Faça uma tabela com os preços da cambada de peixes e no final destaque a cambada de peixe mais barata.

nome_peixe, preco = input().split()
preco_menor = float(preco) 
nome_menor = nome_peixe 
cont = 0 
print("+--------------------+--------------------+")
print("|        peixe       |      preço   R$    |")
print("+--------------------+--------------------+")

if nome_peixe == "fim" and float(preco) < 0:
    print("|           Hoje não tem peixe            |")
    print("+-----------------------------------------+")
else:
    while nome_peixe != "fim" and float(preco) > 0:
        if float(preco) <= (preco_menor):
            preco_menor = float(preco)
            nome_menor = nome_peixe
        str_preco = f'{float(preco):.2f}'
        print(f"| {nome_peixe:<18} | {str_preco:>18} |")
        print("+--------------------+--------------------+")
        nome_peixe, preco = input().split()
        cont +=1

if cont >= 2:
    print("\n+-----------------------------------------+")
    print("|         Cambada de menor preço          |")
    print("+--------------------+--------------------+")
    str_preco = f'{float(preco_menor):.2f}'
    print(f"| {nome_menor:<18} | {str_preco:>18} |")
    print("+--------------------+--------------------+")