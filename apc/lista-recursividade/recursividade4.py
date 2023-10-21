def JaChegou(n, s):
    if n != 0:
        print(s)
        JaChegou(n-1, s)
        
JaChegou(5, 'A gente ja chegou?')
JaChegou(2, 'APC eh melhor que ISC?')
JaChegou(7, 'XD orz \o/ OwO')
