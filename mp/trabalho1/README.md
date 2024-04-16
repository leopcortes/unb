# Como executar o projeto:

Para compilar o programa basta estar no diretório pai (.) e rodar o comando `make`, os testes são feitos automaticamente e o resultado é impresso no terminal.

### Como o projeto foi analizado:

- Os arquivos fonte foram analizados pelo _cpplint_ para estilização utilizando o comando: `make cpplint`.

- Também foram checados pelos analizadores estático (_cppcheck_) e dinâmico (_valgrind_) para procurar erros utlizando os comandos: `make cppcheck` e `make valgrind`.

- A cobertura dos testes foi analizada com o comando: `make gcov`.

- Por fim o programa foi debugado utilizando o comando: `make debug`.
