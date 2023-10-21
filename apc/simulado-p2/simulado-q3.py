"""
Márcia criou um novo aplicativo com recomendações de vídeos... quase, na 
verdade ela ainda não fez a parte das recomendações. Ela pediu a sua ajuda 
para fazer um algoritmo de teste. O algoritmo é bem simples: cada vídeo no 
aplicativo de Márcia possui uma ou mais tags que identificam seu conteúdo. 
Dado o histórico de tags de cada vídeo assistido pelo usuário, o algoritmo 
deve recomendar um vídeo que tenha a tag vista com maior frequência 
anteriormente. Por exemplo, digamos que os vídeos que Márcia viu recentemente 
no seu aplicativo sejam identificados pelas seguintes tags: 
[[gatos, musica], [comida, trendy], [gatos], [estudo], [musica, comida], [gatos, cachorros]]
Então o algoritmo deve recomendar um vídeo com a tag [gatos] pois é a mais 
frequente nos vídeos vistos recentemente por Márcia.

Entrada:
A sua função deve receber uma lista l, (2<= |l| <= 1000), que é o histórico de 
vídeos de algum usuário. Cada elemento Ai dessa lista é uma outra lista 
(1 <= |Ai|<= 50) de strings, que são as tags do vídeo Ai.

Saída:
Sua função deve retornar uma lista com as tags do vídeo recomendado.

"""

def recomendarVideo(lista_de_listas):
    freq = dict()
    m = 0
    for lista in lista_de_listas:
        for tag in lista:
            freq[tag] = freq.get(tag, 0) + 1
            m = max(m, freq[tag])
    resposta = []
    for chave, valor in freq.items():
        if valor == m:
            resposta.append(chave)
    return resposta

l = [["gatos", "musica"], ["comida", "trendy"], ["gatos"], ["estudo"], ["musica", "comida"], ["gatos", "cachorros"]]
print(recomendarVideo(l))