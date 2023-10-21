T, N = map(int, input().split())
if(N > 0):
    tabela_hash = [[] for _ in range(T)]

    chaves = list(map(int, input().split()))
    for chave in chaves:
        idx = chave % T
        tabela_hash[idx].append(chave)

    for i, slot in enumerate(tabela_hash):
        print(f'{i} -', end=' ')
        if not slot:
            print('[x]')
        else:
            print(' -> '.join(map(str, slot)))
else:
    print('0 - [x]')