/**
 * @file frame.c
 * @section DESCRIPTION
 * Universidade de Brasilia\n
 *
 * Leonardo Pereira Cortes - 200030582\n
 *
 * Software Basico - 2024.1\n
 * Professor: Marcelo Ladeira\n\n
 *
 * Arquivo que contem funcoes que manipulam os frames criados e a stack de frames.
 */

#include "../includes/frame.h"

/**
 * @brief Cria uma estrutura de pilha e coloca no frame. Sao necessarios uma
 * referencia a classe q contem o metodo os bytecodes e uma referencia a constant Pool
 * @param cp uma referencia a constant pool
 * @param classe uma referencia a classe
 * @param code uma referencia ao atributo code do metodo atual
 * @return void
 */
void criaFrame(cp_info *cp, classFile *classe, code_attribute *code)
{
	// Aloca espaco para o novo frame
	struct stackFrame *sf = NULL;
	sf = (struct stackFrame *)calloc(sizeof(struct stackFrame), 1);

	if (sf == NULL)
	{
		printf("Problema na alocacao do frame\n");
	}

	sf->refFrame = (struct frame *)calloc(sizeof(struct frame), 1);

	// Empilha o frame na pilha de frames
	pushFrame(cp, classe, code, sf);
}

/**
 * @brief Funcao que empilha na nossa pilha de frames um novo frame alocado
 * @param cp uma referencia a constant pool
 * @param classe uma referencia a classe
 * @param code uma referencia ao atributo code do metodo atual
 * @param sf referencia para a pilha de frames
 * @return void
 */
void pushFrame(cp_info *cp, classFile *classe, code_attribute *code, struct stackFrame *sf)
{
	// Atualiza a pilha.
	sf->next = topo;
	topo = sf;

	// Preenche o frame com as informacoes

	topo->refFrame->pc = 0; // Inicializa o pc

	// Inicializa classe constantPool tamanho da pilha tamanho do array de ver local
	// Inicializa bytecodes
	topo->refFrame->classe = classe;
	topo->refFrame->constant_pool = cp;
	topo->refFrame->max_stack = 2 * code->max_stack + 110;
	topo->refFrame->max_locals = code->max_locals;
	topo->refFrame->code_length = code->code_length;
	topo->refFrame->code = code->code;

	// Aloca espaco para o array de var local
	topo->refFrame->fields = calloc(sizeof(uint32_t), topo->refFrame->max_locals);

	// Aloca espaco para a pilha de operandos e poe indice na pilha na posicao correta
	topo->refFrame->pilha_op = calloc(1, sizeof(pilha_op));
	topo->refFrame->pilha_op->operandos = calloc(topo->refFrame->max_stack, sizeof(uint32_t));
	topo->refFrame->pilha_op->depth = 0; // inicialmente a pilha esta vazia

	// Atualiza o frameCorrente para o frame alocado agora
	// Importante para que o loop de execucao acesse o frameCorrente atualizado
	frameCorrente = topo->refFrame;
}

/**
 * @brief Funcao que desempilha na  pilha de frames o frame que terminou a execucao
 * Fesempilha e atualiza o estado da pilha. Se nao tem mais frames na pilha garante
 * que a execucao termine
 * @param void
 * @return void
 */
void popFrame()
{
	struct stackFrame *anterior;
	// Se topo->next diferente de null -> existe outros frames para executar.
	// Atualiza o frame corrente para prosseguir a execucao.
	if (topo->next != NULL)
	{
		frameCorrente = topo->next->refFrame;

		// Empilha valor de retorno do frame anterior na pilha do proximo frame
		// Salva numa var global
		if (flagRet == 1)
		{
			push(retorno);
		}
		else if (flagRet == 2)
		{
			push(retAlta);
			push(retBaixa);
		}
		flagRet = 0;
	}
	else
	{
		frameCorrente = NULL;
	}

	anterior = topo->next; // Salva frame anterior

	// Desaloca frame ja executado.
	free(topo->refFrame->pilha_op->operandos);
	free(topo->refFrame->pilha_op);
	free(topo->refFrame->fields);
	free(topo->refFrame);
	free(topo);

	topo = anterior; // Atualiza topo com o proximo frame a ser executado
}

/**
 * @brief Funcao que desaloca o topo da pilha de frames de metodos
 * @param void
 * @return void
 */
void desalocaFrame()
{
	popFrame();
}

/**
 * @brief Funcao para dar um push na pilha de operandos
 * @param valor int32_t valor, o valor a ser colocado na pilha
 * @return void
 */
void push(int32_t valor)
{
	mostra_profundidade(1);

	if (frameCorrente->pilha_op->depth >= frameCorrente->max_stack)
	{
		printf("Overflow na pilha de operandos!\n");
		exit(0);
	}

	frameCorrente->pilha_op->depth += 1;																						// incrementa profundidade da pilha
	frameCorrente->pilha_op->operandos[frameCorrente->pilha_op->depth - 1] = valor; // poe valor no frame (-1 pois o array comeca em 0)
}

/**
 * @brief Funcao para dar pop na pilha de operandos
 * @param void
 * @return valor a ser colocado na pilha
 */
int32_t pop_op()
{
	mostra_profundidade(-1);
	frameCorrente->pilha_op->depth -= 1; // decrementa profundidade da pilha

	if (frameCorrente->pilha_op->depth < 0)
	{
		printf("profundidade da pilha de operandos negativa: %d\n", frameCorrente->pilha_op->depth);
		printf("pc: %d\n", frameCorrente->pc);
	}

	// Retorna valor se deve ao fato de o topo da pilha ja ter sido decrementado
	return frameCorrente->pilha_op->operandos[frameCorrente->pilha_op->depth];
}

decodificador dec[NUM_INSTRUCAO];

/**
 * @brief Funcao utilizada para debug (mostra a profundidade da pilha de operandos)
 * @param i valor inteiro a ser atualizado na pilha de operandos (para obter a profundidade)
 * @return void
 */
void mostra_profundidade(int i)
{
	int j = 0; // flag para debug
	if (j == 1)
	{
		inicializa_decodificador(dec);
		int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;

		printf("instrucao que modifica pilha: %s\n", dec[frameCorrente->code[frameCorrente->pc]].instrucao);
		printf("valor de pc: %d\n", frameCorrente->pc);
		printf("nova profundidade da pilha: %d\n", frameCorrente->pilha_op->depth + i);
	}
}

/**
 * @brief Funcao criada para analisar o conteudo da pilha de operandos (usada para debug e problemas com stackOverflow)
 * @param void
 * @return void
 */
void dumpStack()
{
	int i;
	printf("\n");
	for (i = 0; i < frameCorrente->pilha_op->depth; i++)
	{
		printf("valor: %d\n", frameCorrente->pilha_op->operandos[i]);
	}
}

/**
 * @brief Funcao criada para analisar o conteudo do array de variaveis locais (usada para debug)
 * @param void
 * @return void
 */
void dumpFields()
{
	int i;
	for (i = 0; i < frameCorrente->max_locals; i++)
	{
		printf("valor: %d\n", frameCorrente->fields[i]);
	}
}
