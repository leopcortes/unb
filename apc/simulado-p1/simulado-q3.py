# Na arte indígenas várias tintas de origem natural são utilizadas. Eles usam o vermelho
# do urucum, o amarelo da curcuma, o preto do jenipapo e branco da tabatinga (argila
# esbranquiçada).

# A tonalidade de cada cor na tela do computador pode ser expressa por meio da codificação 
# RGB (Red-GreenBlue ou Vermelho, Verde e o Azul), que são as cores primárias por adição.

# Cada cor primária é representada por 8 bits, o que misturando as diversas tonalidades das cores
# primárias permitem obter 16.777.216 cores diferentes. Por exemplo, compondo #FF0000 e #00FF00
# temos: rgb(255, 255, 0) em decimal ou #FFFF00 em hexadecimal

# Faça um programa que transforme o RGB em decimal para hexadecimal de algumas cores usadas
# pelos indígenas, como o vermelho urucum.

def dec_para_hex(dec):
    resultado = dec // 16
    resultado = bin_para_hex(resultado)
    resto = dec % 16
    resto = bin_para_hex(resto)
    
    return resultado+resto

def bin_para_hex(bin):
    if bin <= 9:
        return str(bin)
    elif bin == 10:
        return "A"
    elif bin == 11:
        return "B"
    elif bin == 12:
        return "C"
    elif bin == 13:
        return "D"
    elif bin == 14:
        return "E"
    elif bin == 15:
        return "F"  

nome, red, green, blue = input().split(", ")
red = dec_para_hex(int(red))
green = dec_para_hex(int(green))
blue = dec_para_hex(int(blue))
hexa = "#"+red+green+blue

print(f"{nome} {hexa}")