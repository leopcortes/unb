from typing import List

class ExercicioGrafo:
    def todosOsCaminhosParaOAlvo(self, grafo: List[List[int]]):
        # lista de todos os caminhos
        caminhos = []

        # funcao recursiva que vai percorrer o grafo
        def percorrer(grafo: List[List[int]], vertice_atual: int, destino: int, caminho: List[int]):
            # copia o caminho feito ate agora (evita a perda de informacao durante as chamadas recursivas)
            caminho_atual = caminho.copy()

            # adiciona o vertice atual
            caminho_atual.append(vertice_atual)

            # se chegamos no destino, retornamos o caminho feito
            if vertice_atual == destino:
                caminhos.append(caminho_atual)
                return
            
            # vizinhos do vertice atual
            for prox in grafo[vertice_atual]:
                # vemos se eh possivel chegar ao destino a partir do vizinho do vertice atual
                percorrer(grafo, prox, destino, caminho_atual)
        
        # comeca o percurso
        percorrer(grafo, 0, len(grafo)-1, [])

        return caminhos
    
exercicio = ExercicioGrafo()

grafos = [
    [[1,2], [3], [3], []],
    [[4,3,1], [3,2,4], [3], [4], []],
    [[1,2], [3], [4,5], [6], [6,7], [7], [], [8], [6]],
    [[1,8],[2,3], [3,4,5], [4,7], [5,6,7], [8], [8], [8], []],
    [[2], [6], [6], [1], [1], [2], []]
]

for i in range(len(grafos)):
    print(f"Caminhos do grafo {i+1}: {exercicio.todosOsCaminhosParaOAlvo(grafos[i])}")
    