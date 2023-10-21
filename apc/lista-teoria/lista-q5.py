v1, v2, v3 = map(int, input("Digite uma data separada por '/': ").split("/"))

data = ""

if v1 <= 12 and v2 <=12:
    print("Formato de entrada indeterminado!")
elif v1 > 31:
    print(f"{str(v1)}/{str(v2).zfill(2)}/{str(v3).zfill(2)}")
elif v1 >= 12 and v2 <= 12:
    print(f"{str(v3)}/{str(v2).zfill(2)}/{str(v1).zfill(2)}")
elif v1 <= 12 and v2 >= 12:
    print(f"{str(v3)}/{str(v1).zfill(2)}/{str(v2).zfill(2)}")