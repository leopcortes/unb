class Vertex:
    def __init__(self, key):
        self.id = key
        self.connectedTo = {}

    def addNeighbor(self, nbr, weight=0):
        self.connectedTo[nbr] = weight

    def getConnections(self):
        return self.connectedTo.keys()

    def getId(self):
        return self.id

    def getWeight(self, nbr):
       return self.connectedTo[nbr]

class Graph:
    def __init__(self):
        self.vertList = {}
        self.numVertices = 0

    def addVertex(self, key):
        self.numVertices = self.numVertices + 1
        newVertex = Vertex(key)
        self.vertList[key] = newVertex
        return newVertex

    def getVertex(self, n):
        if n in self.vertList:
            return self.vertList[n]
        else:
            return None

    def addEdge(self, f, t, weight=0):
        if f not in self.vertList:
            nv = self.addVertex(f)
        if t not in self.vertList:
            nv = self.addVertex(t)
        self.vertList[f].addNeighbor(self.vertList[t], weight)

    def getVertices(self):
        return self.vertList.keys()
    
def encontrar_caminhos(grafo,i,j):
    caminhos = []
    
    def busca_profundidade(atual, caminho):
        caminho.append(atual)
        if atual == j:
            caminhos.append(caminho[:])
        else:
            for adjacente in grafo.getVertex(atual).getConnections():
                if adjacente.getId() not in caminho:
                    busca_profundidade(adjacente.getId(), caminho)
        caminho.pop()
        
    if grafo.getVertex(i):
        busca_profundidade(i, [])
    
    return caminhos

g = Graph()
g.addEdge("i","x")
g.addEdge("x","j")
print(encontrar_caminhos(g,"i","j"))

g = Graph()
g.addEdge("i","x")
g.addEdge("x","j")
print(encontrar_caminhos(g,"i","z"))

g = Graph()
g.addEdge("i","x")
g.addEdge("x","j")
g.addEdge("i","z")
g.addEdge("z","j")
print(encontrar_caminhos(g,"i","j"))