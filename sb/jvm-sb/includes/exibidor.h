/**
 * @file exibidor.h
 * @section DESCRIPTION
 * Universidade de Brasilia\n
 *
 * Leonardo Pereira Cortes - 200030582\n
 *
 * Software Basico - 2024.1\n
 * Professor: Marcelo Ladeira\n\n
 *
 * Arquivo que contem as declaracoes de funcoes utilizadas pelo exibidor.
 */

#ifndef PRINT_H
#define PRINT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "leitor.h"

void imprimePrompt(classFile *cf);

/**
 * @brief A funcao recebe uma referencia para a CP e a posicao atual da CP
 * imprime a UTF8 associada a essa posicao da tabela
 */
void imprime_string_pool(cp_info *cp, int pos_pool);
void imprime_methods(classFile *cf);
void imprime_code(classFile *cf, code_attribute *cd_atrb);
void imprime_exc(classFile *cf, exceptions_attribute *exc_atrb);
void printAF(uint16_t access_flags);

#endif
