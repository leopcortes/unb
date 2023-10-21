# for numero in [0, 1, 5, 10, 16, 32, 64, 128, 173]:
#     msb = 0
#     if numero != 0:
#         copia = numero
#         while copia != 1:
#             copia = copia >> 1
#             msb += 1
#     print(f"MSB de {numero:03d} é {msb}: {numero:08b}")
#     print(f"               {' '*(8-msb)}^")
#     print("--------------------------")
    
for num in [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 32, 48, 64, 92, 128, 255]:
    msb = 0
    if num != 0:
        copia = num
        while copia != 1:
            copia = copia >> 1
            msb += 1
            
print(f"MSB de {num:03d} é {msb}: {num:08b}")
print(f"               {' '*(8-msb)}^")
print("--------------------------------")