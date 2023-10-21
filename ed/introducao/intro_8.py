def menor_numero_zeros_a_apagar(s):
    s = s.lstrip('0')
    grupos_1 = s.split('1')
    
    if not grupos_1:
        return 0
    
    zeros_meio = sum(len(grupo) for grupo in grupos_1[1:-1])
    
    return zeros_meio

n = int(input())
for _ in range(n):
    s = input().strip()
    print(menor_numero_zeros_a_apagar(s))
