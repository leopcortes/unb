def caminho(s):
    try:
        arquivo = open(s, 'r')
        caminho_absoluto = arquivo.name
        arquivo.close()
        print(f"Voce esta no {caminho_absoluto}")
    except FileNotFoundError:
        print("Apaguei?")