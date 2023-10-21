catalogo = dict()
produtos = input().split()
pedido = input().split()

for i in range(0, len(produtos), 2):
    produto = produtos[i]
    preco = float(produtos[i+1])
    catalogo[produto] = preco
    
total = 0.0

for i in range(0, len(pedido), 2):
    produto = pedido[i]
    quantidade = int(pedido[i+1])
    
    if produto in catalogo:
        preco = catalogo[produto]
        total += preco * quantidade

print(f"R$ {total:.2f}")