# Projeto Final de Software Básico (2024.1) - Java Virtual Machine (JVM)

Grupo Individual: **Leonardo Pereira Cortes (200030582)**

Devido a alguns problemas pessoais acabei não fazendo os trabalhos do Leitor-Exibidor e do Projeto Lógico e por isso acabei ficando sem grupo, logo o desenvolvimento foi feito de forma individual.

## Desenvolvimento do Projeto

### Documentação

O projeto foi documentado utilizando a ferramenta _Doxygen_. Para gerar essa documentação basta estar no diretorio raiz e rodar o comando abaixo. Será gerada um pasta _html_ contendo um arquivo `index.html`, basta abri-lo com um navegador para ver a documentação.

```
make doxygen
```

### Análise

Foram utilizadas ferramentas de análise estática ([cppcheck](http://cppcheck.sourceforge.net/)) e análise dinâmica do código ([valgrind](https://valgrind.org/docs/manual/quick-start.html#quick-start.intro)) para detecção de erros e análise de segurança.

## Build do Projeto

Inicialmente deve-se compilar os arquivos testes (foi utilizado `Javac` com bytecode `Java 8`), para isso, execute comando `make compile_java` **no diretório raiz**:

```
make compile_java
```

Já para a compilação do projeto (feita com `gcc version 9.4.0` e flags `-Wextra -g -m32 -std=c99`), deve-se executar o comando a seguir **no diretório raiz**:

```
make
```

A execucão é feita a partir do arquivo **main** gerado pelo make, passando como parâmetro um arquivo _.class_ e a opção, sendo **0** para execucão do programa e **1** para exibicão do _.class_:

```
./main ARQUIVO OPÇÃO
```

Exemplo:

```
./main HelloWorld.class 0
```

<!-- ### Windows

O projeto foi feito em WSL (_Windows Subsystem for Linux_), que eu recomendaria, porém é possível executá-lo no Windows com o passo a passo a seguir:
Faça um projeto no DevCpp e importe as pastas "_include_", "_src_" e "_tests_" ao projeto. Adicione `-std=c++11` ao parâmetro de compilação de C++ nas opções de projeto. Compile apertando F9 e execute.
A execucão é feita a partir do arquivo **nome_do_projeto.exe** gerado pelo DevCpp, passando como parâmetro um arquivo .class e a opcão, sendo **0** para execucão do programa e **1** para exibicão do _.class_:

```
nome_do_projeto.exe ARQUIVO OPÇÃO
```

Exemplo:

```
JVM.exe HelloWorld.class 1
``` -->

### Informações

Como o projeto foi desenvolvido individualmente, nem todas as funcionalidades foram implementadas, por isso alguns dos códigos de teste podem não executar como esperado, por exemplo:

- `vetor2.class`;
- `multi.class`;
- `Belote.class`;
- `method_test.class`;
- `objeto_teste.class`;

### Referências

- [Livro JVM7](https://docs.oracle.com/javase/specs/jvms/se7/jvms7.pdf)
- [Introducão à JVM](https://www.devmedia.com.br/introducao-ao-java-virtual-machine-jvm/27624)
- [Documentacão JVM](https://www.guru99.com/java-virtual-machine-jvm.html)
- [JVM Specification SE8](https://docs.oracle.com/javase/specs/jvms/se8/html/)
- [Documentacão das Classes](https://docs.oracle.com/javase/7/docs/api/java/io/PrintStream.html)
- [Documentacão das Classes](https://docs.oracle.com/javase/7/docs/api/java/lang/System.html)
- [Understanding JVM Internals](https://www.cubrid.org/blog/3826357)
- [JVM Architecture 1](https://www.youtube.com/watch?v=ZBJ0u9MaKtM)
- [JVM Architecture 2](https://www.youtube.com/watch?v=DXykPdFt1KY)
- [JVM Bytecode for Dummies](https://www.youtube.com/watch?v=rPyqB1l4gko)
- [Exemplo de JVM](https://www.codeproject.com/Articles/24029/Home-Made-Java-Virtual-Machine)
- [Exemplo de JVM](https://www.codeproject.com/Articles/43176/How-to-create-your-own-virtual-machine)
