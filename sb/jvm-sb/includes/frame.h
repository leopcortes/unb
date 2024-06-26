/**
 * @file frame.h
 * @section DESCRIPTION
 * Universidade de Brasilia\n
 *
 * Leonardo Pereira Cortes - 200030582\n
 *
 * Software Basico - 2024.1\n
 * Professor: Marcelo Ladeira\n\n
 *
 * Arquivo que contem as declaracoes de e estruturas e funcoes do frame.
 */

#ifndef FRAME_H
#define FRAME_H

#include <stdint.h>
#include "leitor.h"

void criaFrame(cp_info *cp, classFile *classe, code_attribute *code);
void desalocaFrame();

/**
 * @brief Struct que representa um frame a pilha de operandos da JVM
 */
typedef struct pilha_op
{
	int depth;					// depth da pilha, inicialmente deve ficar em zero (pilha comeca sem operandos)
	int32_t *operandos; // ponteiro para o array de 32 bits de tamanho max_stack
} pilha_op;

/**
 * @brief Struct que representa um frame
 * Cada frame tem seu proprio PC, cada metodo ao ser executado cria um frame proprio
 */
typedef struct frame
{
	int32_t *fields; // Array de variaveis locais
	cp_info *constant_pool;
	classFile *classe;
	uint16_t max_stack;
	uint16_t max_locals;
	uint32_t code_length;
	uint8_t *code;			// Bytecode
	uint32_t pc;				// Program counter
	pilha_op *pilha_op; // Pilha de operandos
} frame;

/**
 * @brief Struct para a pilha de frames de metodos
 */
struct stackFrame
{
	frame *refFrame;
	struct stackFrame *next;
};

/**
 * @brief Struct que representa o array
 * Contem uma referencia ao array e seu respectivo tamanho.
 */
typedef struct array
{
	int32_t referencia;
	int32_t tamanho;
	int8_t tipo;
} vector;

/**
 * @brief Salva o frame que esta sendo executado.
 */
struct frame *frameCorrente;

/**
 * @brief Array de arrays
 */
vector *arrayVetores;

/**
 * @brief Var com a quantidade de arrays no arrayVetores
 */
int32_t qtdArrays;

/**
 * @brief Var global para guardar retorno de um metodo e empilhar no proximo metodo
 */
int32_t retorno;
int32_t retAlta, retBaixa;

/**
 * @brief Flag para empilhar 1 slot ou 2 (double e long)
 */
int8_t flagRet;

/**
 * @brief Funcoes para pilha
 */
void push(int32_t valor);
int32_t pop_op();
void dumpStack();
void dumpFields();
void pushFrame(cp_info *, classFile *, code_attribute *, struct stackFrame *);
void popFrame();
void mostra_profundidade(int i);

/**
 * @brief Refencia ao topo da pilha de frames. Essencial para Empilhar e desempilhar os frames
 */
static struct stackFrame *topo = NULL;

#endif
