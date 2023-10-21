for i in range(8): # Deslocamento do valor 1 binário, de uma casa até 8 casas
    mascara = (0x01 << i) 
    print(f"Valor = {mascara:03d} gera a mascara binaria = {mascara:08b}") # Impressão em 8 casas

x = 10
print(f"\n{x} // {bin(x)} // {hex(x)} // {oct(x)}")

y = x << 2
print(f"{y} // {bin(y)} // {hex(y)} // {oct(y)}")