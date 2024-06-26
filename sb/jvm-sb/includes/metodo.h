/**
 * @file metodo.h
 * @section DESCRIPTION
 * Universidade de Brasilia\n
 *
 * Leonardo Pereira Cortes - 200030582\n
 *
 * Software Basico - 2024.1\n
 * Professor: Marcelo Ladeira\n\n
 *
 * Arquivo que contem as declaracoes de e estruturas e funcoes do metodo.
 */

#ifndef METODO_H
#define METODO_H

#include "carregador.h"

method_info *buscaMetodoMain();
void empilhaMetodo(method_info *, classFile *);
void executaFrameCorrente();
objeto *criaObjeto(classFile *);
method_info *buscaMetodo(classFile *indiceClasse, classFile *searchClasse, uint16_t indice);
int32_t retornaNumeroParametros(classFile *classe, method_info *metodo);
classFile *retornaClasseNome(char *);
int32_t buscaCampo(char *className, char *name, char *desc);

#endif