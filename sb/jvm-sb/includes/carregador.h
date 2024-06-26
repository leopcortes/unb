/**
 * @file carregador.h
 * @section DESCRIPTION
 * Universidade de Brasilia\n
 *
 * Leonardo Pereira Cortes - 200030582\n
 *
 * Software Basico - 2024.1\n
 * Professor: Marcelo Ladeira\n\n
 *
 * Arquivo que contem as declaracoes de funcoes utilizadas pelo carregador.
 */

#ifndef CARREGADOR_H
#define CARREGADOR_H

#include "leitor.h"
#include "area_metodos.h"

extern area_metodos area_met; // Area de metodos.

/**
 * @brief Funcoes usadas no carregador
 */
int32_t carregaMemClasse(char *);
char *retornaNomeClasse(classFile *);
classFile *buscaClasseIndice(int);
char *retornaNome(classFile *cf, uint16_t indiceNome);
int32_t carregaObjectClasse();

#endif
