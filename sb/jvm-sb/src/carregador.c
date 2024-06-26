/**
 * @file carregador.c
 * @section DESCRIPTION
 * Universidade de Brasilia\n
 *
 * Leonardo Pereira Cortes - 200030582\n
 *
 * Software Basico - 2024.1\n
 * Professor: Marcelo Ladeira\n\n
 *
 * Arquivo que contem funcoes para carregar classes nas estruturas adequadas,
 * funcoes auxiliares que retornam nome de classe, nome em um utf8 e a partir
 * da posicao de uma classe no array de classes dentro da area de metodos
 * retorna uma referencia a essa classe.
 */

#include "../includes/carregador.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

area_metodos area_met;		// Area de metodos que engloba o array de classes e seus respectivos metodos
bool ja_carregou = false; // Booleano para verificar a primeira classe a ser carregada

/**
 * @brief Funcao para carregar o Object.class
 * Se ainda nao foi carregado carrega no array de classes
 *
 * @param ObjectClass path do "object.class" a ser carregado no array de classes
 * @return posicao da classe alocada no array de classes
 */
int32_t carregaObjectClasse(char *ObjectClass)
{
	int aux;

	if (ja_carregou == false) // se eh a primeira classe a ser carregada
	{
		area_met.num_classes = 0;
		ja_carregou = true;
	}

	for (int32_t i = 0; i < area_met.num_classes; i++) // se ja esta carregado retorna posicao no array de classes
	{
		if (strcmp(ObjectClass, retornaNomeClasse(area_met.array_classes[i])) == 0)
		{
			return i;
		}
	}

	// Se nao esta carregado carrega salva no array de classes
	// uma classe nova vai entrar na lista de classes carregadas
	area_met.num_classes++;
	aux = area_met.num_classes;

	classFile **arrayClassesTemp = NULL;

	// Realoca o tamanho do vetor para adicionar a nova classe carregada
	// Classes previamente carregas nao sao perdidas com o realloc
	arrayClassesTemp = (classFile **)realloc(area_met.array_classes, (aux * sizeof(classFile *)));
	// printf("ponteiro tempo: %d\n",*arrayClassesTemp);

	area_met.array_classes = (classFile **)calloc(1, sizeof(classFile *));
	area_met.array_classes = arrayClassesTemp;

	// Atualiza o nome do path para adicionar .class a um path
	// Aloca espaço do tamanho do nome da classe mais espaço para .class /0 e ./
	char *destino = malloc(strlen(ObjectClass) + 10);
	if (strstr(ObjectClass, ".class") != NULL)
	{
		sprintf(destino, "%s", ObjectClass);
	}
	else
	{
		sprintf(destino, "./%s.class", ObjectClass);
	}

	// printf("destino: %s\n",destino);

	area_met.array_classes[area_met.num_classes - 1] = leitorClasse(destino);

	if (area_met.array_classes[area_met.num_classes - 1] == NULL)
	{
		printf("Erro ao carregar classe!\n");
		exit(0);
	}

	return aux - 1;
}

/**
 * @brief Funcao para carregar um arquivo .class
 * Se ainda nao foi carregado carrega no array de classes
 * @param nomeClass nome do arquivo ".class" a ser carregado no array de classes
 * @return posicao da classe alocada no array de classes
 */
int32_t carregaMemClasse(char *nomeClass)
{
	int aux;

	if (ja_carregou == false) // se eh a primeira classe a ser carregada
	{
		area_met.num_classes = 0;
		ja_carregou = true;
	}

	for (int32_t i = 0; i < area_met.num_classes; i++) // Se ja esta carregado retorna posicao no array de classes.
	{
		if (strcmp(nomeClass, retornaNomeClasse(area_met.array_classes[i])) == 0)
		{
			return i;
		}
	}

	// Se nao esta carregado carrega e salva no array de classes
	// uma classe nova vai entrar na lista de classes carregadas
	area_met.num_classes++;
	aux = area_met.num_classes;

	classFile **arrayClassesTemp = NULL;

	// Realoca o tamanho do vetor para adicionar a nova classe carregada.
	// Classes previamente carregas nao sao perdidas com o realloc.
	arrayClassesTemp = (classFile **)realloc(area_met.array_classes, (aux * sizeof(classFile *)));
	// printf("ponteiro tempo: %d\n",*arrayClassesTemp);

	area_met.array_classes = (classFile **)calloc(1, sizeof(classFile *));
	area_met.array_classes = arrayClassesTemp;

	// Atualiza o nome do path para adicionar .class a um path
	// Aloca espaço do tamanho do nome da classe mais espaço para .class /0 e ./
	char *destino = malloc(strlen(nomeClass) + 10);
	if (strstr(nomeClass, ".class") != NULL)
	{
		sprintf(destino, "%s", nomeClass);
	}
	else
	{
		sprintf(destino, "./%s.class", nomeClass);
	}

	// printf("destino: %s\n",destino);

	area_met.array_classes[area_met.num_classes - 1] = leitorClasse(destino);

	if (area_met.array_classes[area_met.num_classes - 1] == NULL)
	{
		printf("Erro ao carregar classe!\n");
		exit(0);
	}

	return aux - 1;
}

/**
 * @brief Funcao para retornar o nome da classe fornecidada
 * Acessa a constant pool no campo bytes a partir do index da classe e retorna o nome da classe
 * Necessaria para saber se classe ja foi carregada ou nao
 * @param classe Estrutura classFile de que se deseja obter o nome
 * @return nome da classe fornecida
 */
char *retornaNomeClasse(classFile *classe)
{
	uint16_t thisClass = classe->this_class;
	uint16_t nameIndex = (classe->constant_pool[thisClass - 1]).info.Class.name_index;

	int i;
	char *retorno = (char *)malloc((classe->constant_pool[nameIndex - 1]).info.Utf8.length + 1);
	uint16_t indice = classe->constant_pool[nameIndex - 1].info.Utf8.length;

	for (i = 0; i < indice; i++) // Percorre o bytes na constant pool e salva no retorno.
	{
		retorno[i] = (char)(classe->constant_pool[nameIndex - 1]).info.Utf8.bytes[i];
	}

	retorno[i] = '\0'; // \0 no final do nome da classe a ser retornada

	return retorno;
}

/**
 * @brief Funcao que retorna uma referencia a uma classFile de acordo com o indice
 * Util para encontrar a classe da main no inicio do processamento
 * @param indice Posicao a ser acessada no array de classes
 * @return Referencia a um classFile ou NULL caso nao exista a referencia
 */
classFile *buscaClasseIndice(int indice)
{
	return indice >= area_met.num_classes ? NULL : area_met.array_classes[indice];
}

/**
 * @brief Funcao que retorna um nome de um utf8 a partir de um indice
 * Muito usada como funcao de auxilio para implementar as instrucoes
 * @param cf Referencia a um classFile para acesso a constant pool
 * @param indiceNome indice para acesso a constant pool
 * @return retorna uma string com o nome
 */
char *retornaNome(classFile *cf, uint16_t indiceNome)
{
	int i;

	char *retorno = malloc((cf->constant_pool[indiceNome - 1]).info.Utf8.length + 1); // Aloca espaço.
	uint16_t indice = cf->constant_pool[indiceNome - 1].info.Utf8.length;

	for (i = 0; i < indice; i++) // Percorre o campo bytes de um utf8 para um auxiliar.
	{
		retorno[i] = (char)(cf->constant_pool[indiceNome - 1]).info.Utf8.bytes[i];
	}

	retorno[i] = '\0'; // Adiciona \0 ao final do nome.

	return retorno;
}
