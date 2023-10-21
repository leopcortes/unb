import re

def pegar_modalidade(s):
    if "aluguel" in s.lower() or "alugo" in s.lower() or "alugar" in s.lower():
        return 'Aluguel'
    elif "venda" in s.lower() or "vendo" in s.lower() or "vender" in s.lower():
        return 'Venda'
    
def pegar_tipo(s):
    if "casa" in s.lower():
        return 'Casa'
    elif "apartamento" in s.lower():
        return 'Apartamento'
    
def pegar_endereco(s):
    endereco = re.search(r'(?:Rua|Avenida)\s+.*?\d+', s)
    if endereco:
        return endereco.group(0)
    
def pegar_cep(s):
    cep = re.search(r'\b\d{5}-\d{3}\b', s)
    if cep:
        return cep.group(0).strip(" ,.")
    else:
        return "nao informado"

def pegar_area(s):
    palavras = s.split()
    for i in range(len(palavras)):
        palavra_area = palavras[i].strip('.,')
        if palavra_area == "metros":
            return palavras[i-1]
        elif palavra_area == "m2":
            return palavras[i-1]
    return "nao informado"

def pegar_valor(s):
    palavras = s.split()
    for i in range(len(palavras)):
        if palavras[i].strip(",.") == "reais":
            if palavras[i-1][-1] == "." or palavras[i-1][-1] == ",":
                return palavras[i-1][:-1]
            else:
                return palavras[i-1]
        elif palavras[i][0:2] == "R$":
            if palavras[i][-1] == "." or palavras[i][-1] == ",":
                return palavras[i][2:-1]
            else:
                return palavras[i][2:]
    
    return "nao informado"
    
def pegar_telefone(s):
    telefone = re.findall(r'\b(\d{5}-\d{4}|\d{4}-\d{4})\b', s)
    telefone = ', '.join(map(str, telefone))
    return telefone
    
def pegar_responsavel(s):
    nome_responsavel = []
    palavras = []
    frases = s.split(". ")
    ultima_frase = frases[-1].strip()
    palavras_ultima_frase = ultima_frase.split()
    for palavra in palavras_ultima_frase:
        palavra = palavra.strip(",")
        palavras.append(palavra)

    for i in range(len(palavras)-1, -1, -1):
        if palavras[i] == "Falar" or palavras[i] == "Por" or palavras[i] == "Valor" or palavras[i] == "Fale" or palavras[i] == "Tem":
            break
        elif palavras[i][0].isupper() and len(nome_responsavel) < 3:
            nome_responsavel.insert(0, palavras[i])
        else:
            continue
    return " ".join(nome_responsavel).strip(",.")
    
def montar_anuncio(s):
    modalidade = pegar_modalidade(s)
    tipo = pegar_tipo(s)
    endereco = pegar_endereco(s)
    cep = pegar_cep(s)
    area = pegar_area(s)
    valor = pegar_valor(s)
    telefones = pegar_telefone(s)
    responsavel = pegar_responsavel(s)
    
    print(f"Modalidade: {modalidade}")
    print(f"Tipo: {tipo}")
    print(f"Endereco: {endereco}")
    print(f"CEP: {cep}")
    print(f"Area: {area}")
    print(f"Valor: {valor}")
    if len(telefones) > 10:
        print(f"Telefones: {telefones}")
    else:
        print(f"Telefone: {telefones}")
    print(f"Responsavel: {responsavel}")

s = "Apartamento disponivel para aluguel na Avenida Sao Carlos, numero 542, CEP 13560-010. 140 metros quadrados, confortavel e espacoso. Falar no numero 99245-1777 com Jose Galdino."
# s = "Vendo um apartamento na Rua Alameda dos Crisantemos, 175, CEP 13566-550, proximo ao Bar do Toco, boa localizacao, arejado e com jardim secreto. Valor da venda a combinar. Falar com Rosane Minghim, no numero 99321-9746."
# s = "Apartamento para aluguel na Rua Jacinto Favoretto, 739, bairro Jardim Lutfalla, 87 m2. Valor: R$1.100,00 mensais. Necessário fiador morador de São Carlos. Contato: 99913-4532 ou 9231-8888. Geraldo Garcia Novaes."
# s = "Oportunidade unica. Vendo uma casa na Rua Episcopal, 45, super espacosa, 200 metros quadrados. O valor a vista eh 126.000,00 reais. Aceito permuta de terreno em Ribeirao Preto-SP. Telefone para contato e 9971-1056. Ricardo Campelo."
# s = "Tenho um apartamento para vender na Avenida Getulio Vargas, n. 387, na Vila Irene. O apartamento possui 132 metros quadrados, vazado, poente, 3 quartos, 2 banheiros, 1 cozinha e ar condicionado. Estou pedindo 200000,00 reais. Por favor, falar no numero 81234-9823 com Francisco Louzada."
# s = "Quero alugar uma casa completa, mobiliada, na Avenida Doutor Carlos Botelho, 1245, 13560-250, no Centro, proximo a padaria Guanabara. Valor e demais detalhes devem ser consultados no telefone 2124-2546 com Fernando Osorio."
# s = "Eu nao gostaria, mas estou endividado e preciso vender uma casa na Avenida Francisco Pereira Lopes, n. 7, no Cidade Jardim. A casa possui churrasqueira, piscina, 230 m2, 4 quartos, 1 suite, 3 vagas para carros, 1 sala e 1 quarto de servico. Tem um fusca velho guardado nos fundos, mas precisa quitar 20 parcelas vencidas do IPVA. O valor para venda eh 56234234 reais, mas faco desconto se quiser ficar com a minha sogra que soh sabe reclamar. Contato: 0000-0000. Falar com Illiarde Ubijara, tambem conhecido como jacare."
# s = "9876-5432. Vendo casa na Avenida da vida 13. 12345-678. 2.357,00 reais, 42 m2. Tem de ligar para o J J e perguntar mais detalhes."
# s = "Casa de 42 m2 para venda na Avenida da vida 13. 9876-5432 12345-678 por 2.357 reais. Tem de ligar para o J J J e perguntar mais detalhes."
# s = "12345-678 Avenida da vida 13, 42 m2 de casa para vender. 2357 reais. 9876-5432 09876-5432. Fale com J J."
# s = "9876-5432. Aluguel de apartamento na Rua da Lua 42, 12345-678. R$2.357,00, 13 metros quadrados. J J."
# s = "Alugo apartamento de 13 metros quadrados na Rua da Lua 42 9876-5432 12345-678 por R$2.357. Fale com J J J."
# s = "Rua da Lua 42 12345-678, 13 metros quadrados, apartamento para alugar. R$2357. Ligue dja! 9876-5432 ou 09876-5432. J J J."
# s = input()
montar_anuncio(s)