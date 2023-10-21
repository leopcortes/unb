N, M, K = map(int, input().split())
jogadores = list(map(int, input().split()))
num_atletas_empresario = list(map(int, input().split()))
atletas_empresarios = []

for _ in range(M):
    atletas = list(map(int, input().split()))
    atletas_empresarios.append(atletas)

potenciais_empresarios = set(range(1, M+1))

for equipe in range(1, K+1):
    atletas_equipe = set([i+1 for i, j in enumerate(jogadores) if j == equipe])
    for i, atletas in enumerate(atletas_empresarios):
        if not atletas_equipe.intersection(set(atletas)):
            potenciais_empresarios.discard(i+1)
            
if potenciais_empresarios:
    print(' '.join(map(str, sorted(potenciais_empresarios))))
else:
    print("-1")
