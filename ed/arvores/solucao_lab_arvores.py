class Arvore_Binaria():
    def __init__(self, raiz = None):
        self.nos = {}
        self.raiz = None
        if raiz != None:
            self.raiz = raiz
            self.nos[raiz] = [None, None]

    def add_no(self, no, raiz = None):
        if self.raiz == None:
            self.raiz = no
            self.nos[no] = [None, None]
            return

        if raiz == None:
            raiz = self.raiz

        esq = self.nos[raiz][0]
        dir = self.nos[raiz][1]

        if no < raiz:
            if esq == None: 
                self.nos[raiz][0] = no
                self.nos[no] = [None, None]
            else: 
                self.add_no(no,esq)

        else:
            if dir == None: 
                self.nos[raiz][1] = no
                self.nos[no] = [None, None]
            else: 
                self.add_no(no, dir)

    def pre_order(self, raiz = None):
        if raiz == None: 
            raiz = self.raiz

        ret = []

        esq = self.nos[raiz][0]
        dir = self.nos[raiz][1]

        ret.append(raiz)
        if esq != None:
            ret += self.pre_order(esq)
        if dir != None:
            ret += self.pre_order(dir)

        return ret

    def in_order(self, raiz = None):
        if raiz == None:
            raiz = self.raiz

        ret = []

        esq = self.nos[raiz][0]
        dir = self.nos[raiz][1]

        if esq != None:
            ret += self.in_order(esq)
        ret.append(raiz)
        if dir != None:
            ret +=  self.in_order(dir)

        return ret

    def pos_order(self, raiz = None):
        if raiz == None:
            raiz = self.raiz

        ret = []

        esq = self.nos[raiz][0]
        dir = self.nos[raiz][1]

        if esq != None:
            ret += self.pos_order(esq)
        if dir != None:
            ret += self.pos_order(dir)
        ret.append(raiz)
        
        return ret
    
def pre_order(raiz, inverter = False):
    ret = []
    ret.append(raiz.dado) # adiciona a raiz na travessia

    # verifica subarvore da esquerda
    if not inverter:
        if raiz.esq != None:
            ret += pre_order(raiz.esq)
        if raiz.dir != None:
            ret += pre_order(raiz.dir, True)

    # verifica subarvore da direita (preorder invertida)        
    else:
        if raiz.dir != None:
            ret += pre_order(raiz.dir, True)
        if raiz.esq != None:
            ret += pre_order(raiz.esq)
    
    return ret

def verificaSimetria(raiz):
    esq = pre_order(raiz.esq) if raiz.esq != None else [] # verifica o lado esquerdo
    dir = pre_order(raiz.dir, True) if raiz.dir != None else []  # verifica o lado direito

    return esq == dir # compara as duas travessias