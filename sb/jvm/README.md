# Projeto de Software Básico - Java Virtual Machine (JVM)

Projeto de desenvolvimento de uma JVM.

## Referências

[Documentacão JVM](https://www.guru99.com/java-virtual-machine-jvm.html)
[Introducão à JVM](https://www.devmedia.com.br/introducao-ao-java-virtual-machine-jvm/27624)

## Setup do ambiente

No desenvolvimento do projeto foram utilizadas as ferramentas de checagem estática e checagem dinânica do código. Para checagem estática foi usado o [cppcheck](http://cppcheck.sourceforge.net/) com o comando `make cppcheck` e para checagem dinâmica foi utilizado o [valgrind](https://valgrind.org/) com o comando make `valgrind`.

## Build do projeto

### Linux:

Para compilar o projeto basta executar

```
make
```

na pasta pai do projeto.  
A execucão é feita executando o arquivo **main** gerado pelo make, passando como parâmetro um arquivo .class e a opcão (**0** para exibicão do .class ou **1** para execucão do programa):

```
./main FILE OPTION
```

Exemplo:

```
./main double_aritmetica.class 0
./main double_aritmetica.class 1
```

### Windows:

Faça um projeto no DevCpp e importe as pastas "include" e "src" ao projeto. Adicione `-std=c++11` ao parâmetro de compilação de C++ nas opções de projeto. Compile apertando F9 e rode, conforme o próximo parágrafo.
A execucão é feita executando o arquivo **<nome do projeto>.exe** gerado pelo DevCpp, passando como parâmetro um arquivo .class e a opcão (**0** para exibicão do .class ou **1** para execucão do programa):

```
<nome do projeto>.exe FILE OPTION
```

Exemplo:

```
jvm.exe double_aritmetica.class 0
jvm.exe double_aritmetica.class 1
```
