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

dec = 236

resultado = dec // 16
resultado = bin_para_hex(resultado)

resto = dec % 16
resto = bin_para_hex(resto)

print(resultado+resto)