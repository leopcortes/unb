/**
 * @file area_metodos.h
 * @section DESCRIPTION
 * Universidade de Brasilia\n
 *
 * Leonardo Pereira Cortes - 200030582\n
 *
 * Software Basico - 2024.1\n
 * Professor: Marcelo Ladeira\n\n
 *
 * Arquivo que contem as declaracoes de estruturas da area de metodos.
 */

#ifndef AREA_METODOS_H
#define AREA_METODOS_H

#include "leitor.h"

#define MAX_VAR 256 // Maximo numero de variaveis um objeto pode ter

/**
 * @brief Um campo que o objeto pode armazenar
 */
// c

/**
 * @brief Contem as informacoes para as variaveis de instancias do objeto
 */
union var
{
	int inteiro;
	char caractere;
	float pflutuante;
};

/*
 * O heap contem um ponteiro para a classfile e um vetor de referencias aos objetos
 * daquela classe
 */
// typedef struct heap
// {
//     // ponteiro para as informacoes relativas a classe la na area de metodos
//     classFile* info_classes;

//     // array de ponteiro para as informacoes dos objetos
//     info_obj** objetos;
//     // numero de objetos, assim que o heap for criado deve ser colocado como zero
//     int num_obj;

//     // array de ponteiros para os arrays - que tambem sao armazenados no heap.
// }heap;

/**
 * @brief Struct para a area de metodos
 */
typedef struct area_metodos
{
	classFile **array_classes; // array de classfiles, contem as classes ja carregadas
	int num_classes;					 // numero de classes carregadas em memoria

} area_metodos;

/**
 * @brief Struct que representa um objeto. Usada na instrução new.
 */
typedef struct objeto
{
	classFile *classe;
	struct objeto *superClasse;
	uint32_t *campos;
	uint32_t *indiceCampos;
} objeto;

objeto **heap; // Array de referencias para objetos.

#endif
