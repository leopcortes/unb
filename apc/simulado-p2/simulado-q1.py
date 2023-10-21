"""
Faustino gosta muito de malhar. Porém, ele não pode ir a academia pois tudo está fechado. 
Ele decidiu então fazer alguns exercícios em casa, e um deles é subir e descer escadas! 
Ele gosta muito de se exercitar mas ele gosta também de fazer treinos variados, então 
cada dia ele vai subir e descer apenas os N primeiros degraus da escada (peculiar, não?). 
Faustino quer colocar uma imagem de quantos degraus ele vai subir, mas ele não desenha 
muito bem! Você, grande amigo de Faustino, querendo que ele mantenha a forma, irá então 
criar uma função recursiva escada que recebe como parâmetro um número N e imprima uma 
escada com N degraus. Observe os casos de teste para entender melhor.

Entrada:
Um número inteiro N que indica quantos degraus serão desenhados. A função recursiva escada 
possui apenas um parâmetro que é um número inteiro positivo N.

Saída:
Uma escada com N degraus.

"""

def escadaLeo(N):
    espaço = ""
    if N == 0:
        return
    print(f"{espaço}__")
    for _ in range(N):
        print(f"{espaço}  |__")
        espaço = espaço + "   "
        
def escada(N):
    if N == 0:
        return
    escada(N-1)
    print("#"*N)

# N = int(input())
N = 5
escada(N)
print('\n')
escadaLeo(N)