def bomba_regressiva(tempo_inicial, tempo_policial):
    if tempo_inicial == 5:
        print("Seu tempo está acabando!")
    elif tempo_inicial == 1 and tempo_policial >= tempo_inicial:
        print("Bomba desativada automaticamente!")
        return
    elif tempo_inicial == 1:
        print("Seja rápido. Falta 1 segundo")
    elif tempo_inicial == 0:
        print("Cabum!!!! Explodiu")
        return
    else:
        print(f"Atenção faltam {tempo_inicial} segundos...")
            
    bomba_regressiva(tempo_inicial-1, tempo_policial)

N = int(input())
P = int(input())
bomba_regressiva(N, P)