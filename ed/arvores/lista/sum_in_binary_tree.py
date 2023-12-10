""" 
    Apesar de natural a ideia de partir do no '1' e ir até o no 'n', é um tarefa um tanto complica decidir em qual direcao a
    seguir, se ir para a esquerda ou direita dependendo do valor de destino. Uma ideia para resolver esse problema, seria fazer
    um algoritmo exponencial que analisa cada possibilidade de caminho. Entretanto, pela quantidade enorme de nos, essa solucao fica
    inviavel. Observando o modo de criacao da arvore binaria, vemos que dado um no de valor 'n' sabemos que seus filhos da esquerda e 
    da direita serao '2*n' e '2*n+1'. Tendo isso em mente, podemos fazer o contrario? Dado um no 'n', podemos decobrir seu pai? A res-
    posta e sim! Basta fazermos a divisao inteira desse no 'n'. Por exemplo, quem e o pai do no 57? Sabe-se esse no tem a forma '2*n' ou 
    '2n+1', entao, para descobrir seu pai basta fazer a sua divisao inteira: 57 // 2 = 28. Assim, podemos descobrir a soma do caminho de '1' ate 'n'
    a partir de 'n', onde do 'n' pegamos o pai do 'n', depois o pai do pai de 'n' e assim por diante ate chegar ao no '1'.
 """

t = int(input())
for _ in range(t):
    n = int(input())
    soma = 0

    # enquanto 'n' > 0 significa que quando chamarmos o pai do no '1' 
    # (ninguem visto que ele e a raiz da arvore) a soma chegou ao fim
    while n > 0:
        soma += n #soma o valor do no 'n'
        n = n // 2 # divisao inteira de 'n'
    
    print(soma)