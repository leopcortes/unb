import math

def distancia(x1, y1, x2, y2):
    return math.sqrt((x1 - x2)**2 + (y1 - y2)**2)

n = int(input())

coelho_x, coelho_y = map(float, input().split())
raposa_x, raposa_y = map(float, input().split())

dist_min = float('inf')

buraco_mais_proximo = None

dist_raposa_coelho = distancia(raposa_x, raposa_y, coelho_x, coelho_y)

for _ in range(n):
    buraco_x, buraco_y = map(float, input().split())
    dist_raposa_buraco = distancia(raposa_x, raposa_y, buraco_x, buraco_y)

    if dist_raposa_buraco < dist_raposa_coelho:
        print("O coelho nao pode escapar.")
        break

    if dist_raposa_buraco < dist_min:
        dist_min = dist_raposa_buraco
        buraco_mais_proximo = (buraco_x, buraco_y)

else:
    print(f"O coelho pode escapar pelo buraco ({buraco_mais_proximo[0]:.3f}, {buraco_mais_proximo[1]:.3f}).")
