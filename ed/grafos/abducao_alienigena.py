# constante de infinito
INF = 0x3f3f3f3f3f3f3f3f

class Grafo:
    def __init__(self):
        self.nos = {}

    def get_nos(self):
        return self.nos

    def add_aresta(self, u, v, peso):
        if u not in self.nos:
            self.nos[u] = []
            
        if v not in self.nos:
            self.nos[v] = []

        self.nos[u].append((v,peso))

    def add_no(self, u):
        if u not in self.nos:
            self.nos[u] = []

    def get_filhos(self, u):
        if u not in self.nos: 
            return None
        
        return self.nos[u]
    
    def dijkstra(self, inicio : int, ovni = False):
        # vetor de distancias: o i-esimo elemento corresponde
        # ao i-esimo vertice do grafo, e dist[i] a distancia de
        # inicio ate i
        dist = [INF] * (len(self.nos)+1)
        visitados = [False] * (len(self.nos) +1)

        # define distancial como 0
        dist[inicio] = 0

        fila = []
        # fila: (distância atual, vertice atual)
        fila.append((0,inicio))
        while len(fila) > 0:
            d_atual, no = fila[0][0], fila[0][1]
            fila.pop(0)

            if visitados[no]: continue
            visitados[no] = True

            for prox, peso in self.get_filhos(no):
                # se estivemos computando as menores distancias para o ovni
                # o peso (ou tempo) das arestas sao 1, segundo o problema
                peso = peso if not ovni else 1
                
                # conferimos se eh possivel chegar ao proximo vertice 
                # em uma distancia menor
                if dist[prox] > d_atual + peso:
                    dist[prox] = d_atual + peso
                    fila.append((dist[prox],prox))

        return dist

grafo = Grafo()

n,m,d = map(int, input().split())
for _ in range(m):
    x,y,t = map(int, input().split())
    grafo.add_aresta(x,y,t)
    grafo.add_aresta(y,x,t)

dist_aristenio = grafo.dijkstra(1)
dist_ovni = grafo.dijkstra(d, ovni = True)
        
# confere se aristenio consegue chegar antes do ovni        
if dist_aristenio[n] < dist_ovni[n]: print("SIM")
else: print("NAO")