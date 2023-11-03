# Trabalho 2 OAC
Prof: Ricardo Pezzuol Jacobi<br>
Aluno: Leonardo Pereira Côrtes - 200030582

## Implementação

### Problema
Implementação de um simulador da arquitetura RV32I em linguagem de alto nível (C++). Deve-se implementar a função de execução (```execute()```) das instruções para o subconjunto de instruções indicado. O programa binário a ser executado deve ser gerado a partir do montador RARS, juntamente com os respectivos dados. O simulador deve ler arquivos binários contendo o segmento de código e o segmento de dados para sua memória e executá-lo. 

### Instruções Implementadas
Foram implementadas as instruções:
```
ADD, ADDI, AND, ANDI, AUIPC, BEQ, BNE, BGE, BGEU, BLT, BLTU, JAL, JALR, LB, 
OR, LBU, LW, LUI, SLT, SLTU, ORI, SB, SLLI, SRAI, ARLI, SUB, SW, XOR e ECALL.
```

Também foram implementadas as funções:
```
init();
fetch(instruction_context_st& ic);
decode(instruction_context_st& ic);
print_instr(instruction_context_st& ic);
get_instr_code(uint32_t opcode, uint32_t func3, uint32_t func7);
get_i_format(uint32_t opcode, uint32_t func3, uint32_t func7);
debug_decode(instruction_context_st& ic);
dump_breg();
dump_asm(int start, int end);
dump_mem(int start_byte, int end_byte, char format);
load_mem(const char *fn, int start);
execute(instruction_context_st& ic);
step();
run();
```

### Testes e Resultados
Foram gerados os arquivos em binários das instruções e dos dados presentes no arquivo ```testador.asm``` fornecido, e a partir deles foram realizados os 22 testes com sucesso. Os testes são operações simples para verificar a funcionalidade de cada instrução. O resultado foi de acordo com o esperado, ou seja, o mesmo resultado rodando o arquivo testador na plataforma RARS.<br>
Execução (comandos para realizar podem ser encontrados no final do relatório na seção "Uso"):
```
Teste1 OK
Teste2 OK
Teste3 OK
Teste4 OK
Teste5 OK
Teste6 OK
Teste7 OK
Teste8 OK
Teste9 OK
Teste10 OK
Teste11 OK
Teste12 OK
Teste13 OK
Teste14 OK
Teste15 OK
Teste16 OK
Teste17 OK
Teste18 OK
Teste19 OK
Teste20 OK
Teste21 OK
Teste22 OK
Encerrando programa.
```

## Sobre o Código

### Sistema Operacional
O programa foi desenvolvido em um WSL (Windows Subsystem for Linux) de Ubuntu.

### Compilador
Foi utilizado o compilador g++ version 9.4.0 (Ubuntu 9.4.0-1ubuntu1~20.04.1) 

### IDE
Foi utilizado o editor de texto Visual Studio Code com as extensões necessárias.

### Uso
Para compilar o programa é necessário estar no diretório raiz do programa (**```T2-200030582```**) e executar o comando **```make```**. O arquivo “```sim_riscv```” será criado e para realizar os testes basta rodar o comando **```./sim_riscv```**. Também é possível compilar usando os comandos:

```
g++ -c -o src/obj/memoria.o src/memoria.cpp -g -Wall -I./include
g++ -c -o src/obj/riscv.o src/riscv.cpp -g -Wall -I./include
g++ -o sim_riscv src/obj/memoria.o src/obj/riscv.o
```