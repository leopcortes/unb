def conteudo_estudado(plano, turno):
    return all(plano.count(c) >= turno.count(c) for c in turno)

n = int(input())

for _ in range(n):
    plano_estudos = input()
    turno_matutino = input()
    turno_vespertino = input()
    turno_noturno = input()
    
    conteudos_estudados = set()
    
    for conteudo in plano_estudos:
        if not conteudo_estudado(conteudos_estudados, turno_matutino):
            if plano_estudos.count(conteudo) > turno_matutino.count(conteudo):
                print("You died!")
                break
        if not conteudo_estudado(conteudos_estudados, turno_vespertino):
            if plano_estudos.count(conteudo) > turno_vespertino.count(conteudo):
                print("You died!")
                break
        if not conteudo_estudado(conteudos_estudados, turno_noturno):
            if plano_estudos.count(conteudo) > turno_noturno.count(conteudo):
                print("You died!")
                break
        
        conteudos_estudados.add(conteudo)
    
    if conteudo_estudado(conteudos_estudados, turno_matutino) and \
        conteudo_estudado(conteudos_estudados, turno_vespertino) and \
        conteudo_estudado(conteudos_estudados, turno_noturno):
        conteudos_estudados = sorted(conteudos_estudados)
        if conteudos_estudados:
            print(f"Bora ralar: {''.join(conteudos_estudados)}")
        else:
            print("It's in the box!")

