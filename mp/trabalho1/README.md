# Executando o projeto

Para compilar o programa basta estar no diretório pai (trabalho1) e rodar o comando `make`

Será gerado um arquivo executável `romano`, e para testar uma conversão de romano para decimal, basta rodar o comando `./romano <string_do_numero_romano>`

Os arquivos fonte foram analizados pelos analizadores estático e dinâmico para procurar erros utlizando os comandos:

- `cppcheck --enable=warning ./src`
- `valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./romano X`
