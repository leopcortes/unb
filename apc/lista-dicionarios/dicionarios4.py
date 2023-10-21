n = int(input())

dicionario = dict()
aluno_presente = False

for _ in range(n):
    nome, email, nota1, nota2, nota3, nota4 = input().split()
    nota1, nota2, nota3, nota4 = map(float, (nota1, nota2, nota3, nota4))
    media = (nota1 + nota2 + nota3 + nota4)/4
    dicionario[nome] = {'email': email, 'media': media}
    
nome_destino = input()

if nome_destino in dicionario:
    info_aluno = dicionario[nome_destino]
    email = info_aluno['email']
    media = info_aluno['media']
    print(f"Destinatário: {email}")
    if media >= 5:
        print(f"O aluno {nome_destino} foi aprovado com média {media:.2f}.")
    else:
        print(f"O aluno {nome_destino} foi reprovado com média {media:.2f}.")    
else:
    print(f"O aluno {nome_destino} não está na turma.")
        