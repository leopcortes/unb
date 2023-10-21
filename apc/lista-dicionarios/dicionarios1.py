def print_hist(h):
  for c in h:
    if h[c] == 0:
        continue
    else:
        print(c, h[c])

frase = input()

contD = 0
contT = 0
contV = 0

for i in frase:
    if i == "d" or i == "D":
        contD += 1
    elif i == "t" or i == "T":
        contT += 1
    elif i == "v" or i == "V":
        contV += 1
        
dicionario = dict()
dicionario['d'] = contD
dicionario['t'] = contT
dicionario['v'] = contV

print_hist(dicionario)