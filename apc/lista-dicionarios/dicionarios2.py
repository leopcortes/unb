n = int(input())

alunos = {}
notas = {}

for _ in range(n):
    nome, nota = input().split(", ")
    nota = float(nota)

    if nota in alunos:
        alunos[nota].append(nome)
    else:
        alunos[nota] = [nome]

    if nota in notas:
        notas[nota] += 1
    else:
        notas[nota] = 1

minha_nota = float(input())

if minha_nota in alunos:
    alunos_com_mesma_nota = alunos[minha_nota]
    if len(alunos_com_mesma_nota) > 1:
        alunos_com_mesma_nota.sort()
        print("/".join(alunos_com_mesma_nota))
    else:
        print("".join(alunos_com_mesma_nota))
else:
    print("Você foi o único aluno com essa nota.")
