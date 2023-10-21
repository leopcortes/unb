qnt_funcionarios = int(input())

nome_menor = ""
salario_menor = 1000000000
nome_maior = ""
salario_maior = 0
soma_salarios = 0

for i in range(qnt_funcionarios):
    nome, salario = input().split(',')
    salario = float(salario)
    soma_salarios += salario
    if salario < salario_menor:
        salario_menor = salario
        nome_menor = nome
    if salario > salario_maior:
        salario_maior = salario
        nome_maior = nome

if qnt_funcionarios == 0:
    print("Nao tem media\nNao tem\nNao tem")
else:
    media = soma_salarios/qnt_funcionarios
    print(f"{media:.2f}")
    print(f"{nome_maior} {salario_maior:.2f}")
    print(f"{nome_menor} {salario_menor:.2f}")

