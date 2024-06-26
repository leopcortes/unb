/**
 * @file decodificador.h
 * @section DESCRIPTION
 * Universidade de Brasilia\n
 *
 * Leonardo Pereira Cortes - 200030582\n
 *
 * Software Basico - 2024.1\n
 * Professor: Marcelo Ladeira\n\n
 *
 * Arquivo que contem as declaracoes de e estruturas e funcoes do decodificador.
 */

#ifndef DECODIFICADOR_H
#define DECODIFICADOR_H

#include <string.h>

#define NOME_INSTRUCAO 30

/**
 * @brief Struct para decodificar um opcode no nome da instrucao conveniente,
 * contem tambem o numero de operandos que a instrucao le
 */
typedef struct decodificador
{
	char instrucao[NOME_INSTRUCAO]; // nome da instrucao
	int bytes;											// numero de bytes que seguem a instrucao
} decodificador;

/**
 * @brief funcao que coloca o nome das strings no decodificador,
 * juntamente com a quantidade em bytes
 */
void inicializa_decodificador(decodificador dec[]);

#endif
