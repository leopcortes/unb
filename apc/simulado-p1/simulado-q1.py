# Belém do Solimões, distrito do município de Tabatinga-AM, é considerada a maior comunidade indígena do Brasil, Esta comunidade
# possui mais de cinco mil indígenas da etnia Ticuna. Na amazônia o meio de transporte mais utilizado é fluvial. Não existem estradas
# até Belém do Solimões.
# A UnB aplica o vestibular indígena em várias regiões do Brasil. Para os candidatos indígenas de Belém do Solimões, a sede mais
# próxima para fazer a prova é em Tabatinga-AM. Existem três tipos de barcos que fazem o trajeto:
# 1) Canoa;
# 2) Voadeira; e
# 3) Barco de transporte.
# O transporte de canoa custa R$ 60,00 por pessoa e a viagem dura 6 horas. A capacidade da canoa é de 6 passageiros. A viagem
# de voadeira custa R$ 120,00 , dura 2 horas e a capacidade da voadeira é de 8 passageiros. Tanto a canoa como a voadeira saem a
# qualquer hora para Tabatinga-AM. A viagem de barco dura x horas e custa R$ 40,00 por passageiro. O barco vem de Manaus e para
# em Belém do Solimões às 14:00 h. O barco pode levar até 200 passageiros, mas chega bem cheio em Belém de Solimões.
# O vestibular indígena em Tabatinga é realizado às 14:00 h. Para isso, o transporte precisa chegar antes da 13:00 h ou no dia anterior.
# Se chegar no dia anterior, deve-se acrescentar um custo extra de R$ 65,00 por pessoa referente a hospedagem e alimentação.
# Faça um programa que leia a quantidade de pessoas, o tipo de transporte e calcule o custo por pessoa para fazer o vestibular em
# Tabatinga-AM.

qnt_pessoas, transporte = input().split()

if transporte == "C":
    valor_por_pessoa = 60 * int(qnt_pessoas)
    print(f"Para transportar {qnt_pessoas} passageiros de canoa sairá R$ {float(valor_por_pessoa):.2f}.")
elif transporte == "V":
    valor_por_pessoa = 120 * int(qnt_pessoas)
    print(f"Para transportar {qnt_pessoas} passageiros de voadeira sairá R$ {float(valor_por_pessoa):.2f}.")
elif transporte == "B":
    valor_por_pessoa = (40 + 65) * int(qnt_pessoas)
    print(f"Para transportar {qnt_pessoas} passageiros de barco sairá R$ {float(valor_por_pessoa):.2f}.")