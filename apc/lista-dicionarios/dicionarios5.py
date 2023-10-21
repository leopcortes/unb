n = int(input())
corredores = dict()

for i in range(1, n+1):
    entrada = input().split()
    produtos = {}
    for j in range(0, len(entrada), 2):
        produto = entrada[j]
        preco = float(entrada[j+1])
        produtos[produto] = preco
    corredores[i] = produtos

corredor = int(input())

if corredor in corredores:
    print(f"No corredor {corredor} encontramos:")
    produtos = corredores[corredor]
    produtos_lista = list(produtos.keys())
    media = sum(produtos.values()) / len(produtos)
    print(", ".join(produtos_lista))
    print(f"E o preço médio é {media:.2f}.")
else:
    print("Esse corredor não existe no mercado.")