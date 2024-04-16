Como executar o projeto

Para compilar o programa basta estar no diretório pai (trabalho1) e rodar o comando `make`, os testes são feitos automaticamente e o resultado é impresso no terminal.

Os arquivos fonte foram analizados pelos analizadores estático e dinâmico para procurar erros utlizando os comandos:
- `cppcheck --enable=warning romanos.cpp`
- `valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./testa_romanos`
