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

    # def pre_order(self, raiz = None):
    #     if raiz == None: 
    #         raiz = self.raiz

    #     ret = []

    #     esq = self.nos[raiz][0]
    #     dir = self.nos[raiz][1]

    #     ret.append(raiz)
    #     if esq != None:
    #         ret += self.pre_order(esq)
    #     if dir != None:
    #         ret += self.pre_order(dir)

    #     return ret

    # def in_order(self, raiz = None):
    #     if raiz == None:
    #         raiz = self.raiz

    #     ret = []

    #     esq = self.nos[raiz][0]
    #     dir = self.nos[raiz][1]

    #     if esq != None:
    #         ret += self.in_order(esq)
    #     ret.append(raiz)
    #     if dir != None:
    #         ret +=  self.in_order(dir)

    #     return ret

    def pos_order(self, raiz = None):
        # raiz == None significa que estamo chamando a funcao 
        # na raiz da arvore binaria de busca em si
        if raiz == None:
            raiz = self.raiz

        # vetor de retorno
        ret = []

        # subarvore da esquerda
        esq = self.nos[raiz][0]
        
        # subarvore da direita
        dir = self.nos[raiz][1]

        # se tiver subarvore, adiciona a ordem pos-order da subarvore da esquerda na resposta
        if esq != None:
            ret += self.pos_order(esq)

        # se tiver subarvore, adiciona a ordem pos-order da subarvore da direita na resposta
        if dir != None:
            ret += self.pos_order(dir)

        # adiciona a raiz da arvore atual no vetor de retorno
        ret.append(raiz)
        
        return ret

arvore_binaria = Arvore_Binaria()
while True:
    try:
        no = int(input())

        # adiciona um no na arvore binaria de busca
        arvore_binaria.add_no(no)
    
    except EOFError:
        break

# resposta = vetor contendo a pos-order da arvore
ans = arvore_binaria.pos_order()
for no in ans:
    print(no)
    