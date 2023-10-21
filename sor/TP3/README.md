# Caça palavras feito para matéria SOR - UnB
  
Projeto procura, em um arquivo de texto de entrada, uma lista de palavras em um diagrama de letras e indica se cada palavra foi encontrada ou não. Caso a palavra seja encontrada, ela é colocada em letras maiúsculas. Os demais caracteres não são modificados. As palavras são procuradas em todas as 8 direções possíveis (linha, coluna, diagonais, de trás para frente). O arquivo de entrada deverá conter o tamanho do diagrama (linhas e colunas), o diagrama e uma lista de palavras. O arquivo de saída irá conter o diagrama com as palavras encontradas em letras maiúsculas.
  
Compilação: g++ cacapalavra.cpp -o cacapalavra  
Execução:   ./cacapalavra entrada.txt saida.txt  
  
Exemplo de arquivo de entrada:  
15 60  
runkffxscslvqwvtvfolwymmxprocessoslkqoifheurjzqbdlpybntwiblv  
xjhjguvykdfrjzltbbweoldpyiymizzdyinjqjfoukvluuypvancozhgzfuk  
htphdcttoyjiketgysvwujakkphslomvxhlfmpyfdyqniuhpvbmtxvtjhact  
qqooatbvmttswtkkdftscwhvveeoemqifgztuzxplqkfofqyjxtdzrkumpkt  
bcbgkhabfbywnojsdokdxhzbgqncfcoyfqblbcpidngserlhgxmfflileyql  
aejivrkvyokguyomsinaisegznoxzvcneptcfeeknmhzifqunkudyyjylxxn  
tbazqetdyxhkmwrongydanpvqotcohbluwmuvcpacokmagfpoftoukjlyfpo  
mqzinalckqtlshvvhjdoyruthogrbeyqtmjuuwgyiyrvsaszjvqjokfwalpc  
rpumbddhvbpvminmhhoahzvzimjpilazpsokeppnmtchfrvmzjoikmhxsyqk  
ibkhtsevdlkuuyyndfuuajtlxbvjiphazpemyxstcdfwedmhkgbmpvzepwuy  
hmijnznzykuqtoxzlbezirhmdxhdmfzmoluybulauywnmumzxtyikiutpfbs  
tiuhxheviyrglughhvbwubpvjbddqkglfofmnmqivqrgkxpuutqpuhmudiri  
ydojieqwsadpcahtistxonqeemnsrvjzvmphwuxtociqcpkmjfmzsedmzrsr  
indklrzsotphhurayiklurxtjdzkurefhhpsyokmkbvtvotuzfhtweoihpse  
hwlqdaaiequsavoutenpdvwyrcnzjespnqadwcnathstfipanfpqalrrngry  
threads  
arquivos  
sinais  
pipe  
processos  
mutex 
  
Arquivo de saída esperado:  
runkffxscslvqwvtvfolwymmxPROCESSOSlkqoifheurjzqbdlpybntwiblv  
xjhjguvykdfrjzltbbweoldpyIymizzdyinjqjfoukvluuypvancozhgzfuk  
htphdcttoyjiketgysvwujakkPhslomvxhlfmpyfdyqniuhpvbmtxvtjhact  
qqooaTbvmttswtkkdftscwhvvEeoemqifgztuzxplqkfofqyjxtdzrkumpkt  
bcbgkHabfbywnojsdokdxhzbgqncfcoyfqblbcpidngserlhgxmfflileyql  
aejivRkvyokguyomSINAISegznoxzvcneptcfeeknmhzifqunkudyyjylxxn  
tbazqEtdyxhkmwrOngydanpvqotcohbluwmuvcpacokmagfpoftoukjlyfpo  
mqzinAlckqtlshVvhjdoyruthogrbeyqtmjuuwgyiyrvsaszjvqjokfwalpc  
rpumbDdhvbpvmInmhhoahzvzimjpilazpsokeppnmtchfrvmzjoikmhXsyqk  
ibkhtSevdlkuUyyndfuuajtlxbvjiphazpemyxstcdfwedmhkgbmpvzEpwuy  
hmijnznzykuQtoxzlbezirhmdxhdmfzmoluybulauywnmumzxtyikiuTpfbs  
tiuhxheviyRglughhvbwubpvjbddqkglfofmnmqivqrgkxpuutqpuhmUdiri  
ydojieqwsAdpcahtistxonqeemnsrvjzvmphwuxtociqcpkmjfmzsedMzrsr  
indklrzsotphhurayiklurxtjdzkurefhhpsyokmkbvtvotuzfhtweoihpse  
hwlqdaaiequsavoutenpdvwyrcnzjespnqadwcnathstfipanfpqalrrngry  
