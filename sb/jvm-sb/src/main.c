/**
 * @file main.c
 * @section DESCRIPTION
 * Universidade de Brasilia\n
 *
 * Leonardo Pereira Cortes - 200030582\n
 *
 * Software Basico - 2024.1\n
 * Professor: Marcelo Ladeira\n\n
 *
 * Funcao main do processamento do arquivo .class e execucao das instrucoes -> JVM.
 *
 * Para compilar:	make clean && make\n
 * Para executar:	./main nome_do_arquivo.class 1  // 1 para printar o classfile.\n
 *                ./main nome_do_arquivo.class 0  // 0 para nao printar o classfile.\n
 *			    	    ./main 			                    // Programa pede pelo .class e opcao de print.\n
 */

#include "../includes/exibidor.h"
#include "../includes/instrucao.h"
#include "../includes/carregador.h"
#include "../includes/metodo.h"

#define arqSize 100

/**
 * @brief Salva nome do arquivo passado via linha de comando.
 */
char *arquivo;

/**
 * @brief Flag para printar no prompt (1 printa e 0 nao printa)
 */
int printPrompt = 0;

/**
 * @brief Inicio da execucao da jvm
 * @param argc argumentos passados via linha de comando
 * @param argv[1] Primeiro argumento eh o .class que contem a main
 * @param argv[2] Segundo argumento eh flag para printar no prompt (1 printa e 0 nao printa)
 */
int main(int argc, char *argv[])
{

	arquivo = calloc(arqSize, sizeof(char));

	/**
	 * @brief Ponteiro para uma estrutura de method_info. Para comecar executando a main
	 */
	method_info *Main;

	/**
	 * @brief 1 - Verifica argumentos por linha de comando
	 */
	if (argc < 3)
	{
		printf("Forneca o .class que contem a main: \n");
		scanf("%s", arquivo);
		getchar();

		printf("Deseja imprimir no prompt? 1 - SIM / 0 - NAO \n");
		scanf("%d", &printPrompt);
	}
	else
	{
		strcpy(arquivo, argv[1]);
		if (*argv[2] == '1')
			printPrompt = 1;
	}

	/**
	 * @brief 2 - Carrega no array de classes o object.class
	 */
	carregaObjectClasse("java/lang/Object");

	/**
	 * @brief 3 - Carrega no array de classes o .class passado por linha de comando
	 */
	carregaMemClasse(arquivo);
	classFile *mainClass = buscaClasseIndice(1);

	/**
	 * @brief 4 - Busca o metodo main para comecar a execucao
	 */
	Main = buscaMetodoMain();

	if (Main == NULL) // Se nao encontrou o main o .class passado esta errado
	{
		printf("Forneca um .class via linha de comando com o metodo main.");
		return 0;
	}

	/**
	 * @brief 5 - Cria frame e coloca na pilha. Passa o metodo com o bytecode
	 * e a classe que contem o metodo com a constantPool
	 */
	empilhaMetodo(Main, mainClass);

	/**
	 * @brief 6 - Executa o metodo main que esta no topo da stackFrame
	 */
	executaFrameCorrente();

	/**
	 * @brief 7 - Se for passado 1 na linha de comando imprime no prompt
	 */
	if (printPrompt)
		for (int i = 1; i < area_met.num_classes; i++)
			imprimePrompt(area_met.array_classes[i]);

	return 0;
}
