numero = 0x0ACE1 # seed inicial

print(numero)

bit0 = numero & 0x01
bit2 = (numero >> 2) & 0x01
bit3 = (numero >> 3) & 0x01
bit5 = (numero & (0x01 << 5)) >> 5

xor0 = bit0 ^ bit2
xor1 = xor0 ^ bit3
xor2 = xor1 ^ bit5
numero = numero >> 1
numero = numero | xor2 << 15

print(numero)