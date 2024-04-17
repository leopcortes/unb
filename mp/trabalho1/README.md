# Como executar o projeto:

Para compilar o programa basta estar no diretório pai (.) e rodar o comando `make`, os testes são feitos automaticamente e o resultado é impresso no terminal.

### Como o projeto foi analisado:

- Os arquivos fonte foram analisados pelo _cpplint_ para estilização utilizando o comando: `make cpplint`.

- Também foram checados pelos analisadores estático (_cppcheck_) e dinâmico (_valgrind_) para procurar erros utlizando os comandos: `make cppcheck` e `make valgrind`.

- A cobertura dos testes foi analisada com o comando: `make gcov`.

- Por fim o programa foi debugado utilizando o comando: `make debug`.
