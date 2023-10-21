def calcular_conta(pratos, prato):
    total = 0
    for linha in pratos:
        nome, preco = linha.split('/')
        preco = float(preco)
        if prato.lower() in nome.lower():
            print(f"{nome} {preco:.2f}")
            total += preco
    return total

arquivo_cardapio = open('cardapio.txt', 'r') 
pratos = arquivo_cardapio.readlines()

prato = input()

conta = calcular_conta(pratos, prato)

if conta > 0:
    print(f"Sua conta deu: {conta:.2f}")
else:
    print("Infelizmente não temos este prato")

arquivo_carteira = open('carteira.txt', 'r')

linha1_carteira = arquivo_carteira.readline()
dinheiro, qnt_dinheiro = linha1_carteira.split('/')
qnt_dinheiro = float(qnt_dinheiro)

linha2_carteira = arquivo_carteira.readline()
cartao, qnt_cartao = linha2_carteira.split('/')
qnt_cartao = float(qnt_cartao)

if qnt_dinheiro >= conta:
    print("Vou pagar com dinheiro")
elif qnt_cartao >= conta:
    print("O jeito é pagar com o cartão de crédito")
else:
    print("Ah não! Vou ter que lavar prato!")