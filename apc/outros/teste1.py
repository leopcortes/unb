resultados_moodle = [10, 7, 9, 6, 4, 8, 5]
num_alunos = len(resultados_moodle)
NUM_LEs = 10  # número de listas de exercícios
NOTA_TRABALHO = 10  # índice da nota do trabalho

medias = [0] * num_alunos
media_geral = 0

for i in range(num_alunos):
    for j in range(NUM_LEs):
        medias[i] += resultados_moodle[i][j] / NUM_LEs
    
    medias[i] = (medias[i] * 0.4) + (resultados_moodle[i][NOTA_TRABALHO] * 0.6)

    media_geral += medias[i]

print(f'A media geralé {media_geral}.')