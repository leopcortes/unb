def mensagem_hora(hora):
    if hora <= 12:
        return "Bom dia!"
    elif hora > 12 and hora < 18:
        return "Bom tarde!"
    else:
        return "Boa noite!"

dia, hora = input().split(',')
hora = int(hora)

if dia == "Sexta":
    print("Sextou!")
    print(mensagem_hora(hora))
else:
    print(mensagem_hora(hora))