n = int(input())
periodos = []

for i in range(n):
    periodos.append(input())

periodos_com_sujeito = []

for periodo in periodos:
    periodo_com_sujeito = "Raimundo Nonato " + periodo
    periodos_com_sujeito.append(periodo_com_sujeito)

for periodo_com_sujeito in periodos_com_sujeito:
    print(periodo_com_sujeito)