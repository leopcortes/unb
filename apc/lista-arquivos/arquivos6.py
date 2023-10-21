def obterNomeUsuario(nlinha):
    fin = open('/etc/passwd', 'r')
    linhas = fin.readlines()
    linha_desejada = linhas[nlinha - 1] 
    campos = linha_desejada.split(':')
    nome = campos[0].strip()
    return nome

linha = int(input())
print(obterNomeUsuario(linha))