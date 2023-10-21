n = int(input("Digite a quantidade de pontos: "))

x, y = [], []

for i in range(n):
    a, b = map(int, input(f"Coordenadas do ponto {i+1}: ").split())
    x.append(a)
    y.append(b)

distance, p1, p2 = None, None, None

for i in range(1, len(x)):
    for j in range(0, i):
        d = (((x[j] - x[i])**2) + ((y[j] - y[i])**2))**(1/2)
        if distance is None or d < distance:
            distance = d
            p1 = j
            p2 = i

print("Os pontos mais próximos são: ")
print(f"Ponto {p1+1} ({x[p1]}, {y[p1]}) e Ponto {p2+1} ({x[p2]}, {y[p2]})")
print(f"Distancia = {d:.2f}")