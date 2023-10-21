def adicionar_disciplina(grade, codigo, horarios):
    for horario in horarios:
        dia, turno, hora = horario[0], horario[1], horario[2:]
        if dia not in grade:
            grade[dia] = {}
        if hora not in grade[dia]:
            grade[dia][hora] = []
        grade[dia][hora].append(codigo)


def remover_disciplina(grade, codigo, horarios):
    for horario in horarios:
        dia, turno, hora = horario[0], horario[1], horario[2:]
        if dia in grade and hora in grade[dia]:
            if codigo in grade[dia][hora]:
                grade[dia][hora].remove(codigo)
                if not grade[dia][hora]:
                    del grade[dia][hora]
            if not grade[dia]:
                del grade[dia]


def mostrar_grade_horaria(grade):
    dias = ['Seg', 'Ter', 'Qua', 'Qui', 'Sex', 'Sab']
    turnos = {'M': 'manhã', 'T': 'tarde', 'N': 'noite'}
    horarios = ['07:30 - 08:25', '08:30 - 09:25', '09:40 - 10:35', '10:40 - 11:35',
                '11:50 - 12:45', '12:50 - 13:45', '14:00 - 14:55', '15:00 - 15:55',
                '16:10 - 17:05', '17:10 - 18:05', '18:50 - 19:45', '19:50 - 20:45',
                '20:50 - 21:45', '21:50 - 22:45', '22:50 - 23:45']

    print('+---------------+----------+----------+----------+----------+----------+----------+')
    print('|               |', end=' ')
    print(' | '.join(dias), end=' |\n')
    print('+---------------+----------+----------+----------+----------+----------+----------+')

    for i, horario in enumerate(horarios):
        print(f'| {horario} |', end=' ')
        for j, dia in enumerate(dias):
            if dia in grade and horario in grade[dia]:
                disciplinas = grade[dia][horario]
                print(' | '.join(disciplinas), end=' ')
            else:
                print(' ', end=' ')
            if j < len(dias) - 1:
                print('|', end=' ')
        print('|')

        if i < len(horarios) - 1:
            print('+---------------+----------+----------+----------+----------+----------+----------+')

    print('+---------------+----------+----------+----------+----------+----------+----------+')


def main():
    grade_horaria = {}

    while True:
        instrucao = input().split()

        if instrucao[0] == '+':
            codigo = instrucao[1]
            horarios = instrucao[2:]
            adicionar_disciplina(grade_horaria, codigo, horarios)
        elif instrucao[0] == '-':
            codigo = instrucao[1]
            horarios = instrucao[2:]
            remover_disciplina(grade_horaria, codigo, horarios)
        elif instrucao[0] == '?':
            mostrar_grade_horaria(grade_horaria)
        elif instrucao[0] == 'Hasta' and instrucao[1] == 'la' and instrucao[2] == 'vista,' and instrucao[3] == 'beibe!':
            break
        else:
            print(f'!{instrucao}')

if __name__ == '__main__':
    main()
