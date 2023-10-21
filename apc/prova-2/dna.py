dna = input() # pega o dna completo do usuário
N = int(input()) # pega o número de doenças do usuário
lista_doencas = []

for _ in range(N): # para o número de doenças
	doenca = input() # pega a doença do usuário
	doenca = doenca.split() # adiciona cada palavra em uma lista
	dna_doenca = doenca.pop(0) # salva o código do dna da lista
	nome_doenca = " ".join(doenca) # salva o resto da lista como nome
	lista_doencas.append(nome_doenca) # adiciona o nome numa lista para todas as doenças

lista_formatada = ", ".join(sorted(lista_doencas)) # ordena a lista em ordem alfabética e formata
if len(lista_doencas) == 0: # se não tiver doenças
	print("Nenhuma doenca encontrada.")
else: # se tiver doenças
	print(f"{len(lista_doencas)} doencas encontradas: {lista_formatada}.")