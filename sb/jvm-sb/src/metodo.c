/**
 * @file metodo.c
 * @section DESCRIPTION
 * Universidade de Brasilia\n
 *
 * Leonardo Pereira Cortes - 200030582\n
 *
 * Software Basico - 2024.1\n
 * Professor: Marcelo Ladeira\n\n
 *
 * Software Basico - 1/2016\n
 * Professor: Marcelo Ladeira\n\n
 *
 * Arquivo que contem funcoes responsaveis por manipular os metodos que serao usados nos frames.
 */

#include "../includes/frame.h"
#include "../includes/metodo.h"
#include "../includes/instrucao.h"
#include "../includes/area_metodos.h"

/**
 * @brief Referencia externa do frame corrente para acesso ao topo da stackFrame
 */
extern struct frame *frameCorrente;

/**
 * @brief Salva a quantidade de objetos alocados (new)
 */
uint32_t numObjetos = 0;

/**
 * @brief Funcao para retornar uma referencia ao metodo main do primeiro .class carregado
 * @param void
 * @return method_info* uma referencia ao metodo main
 */
method_info *buscaMetodoMain()
{
	classFile *main;
	uint16_t nome_tam, desc_tam;
	uint8_t *nome;
	uint8_t *desc;

	main = buscaClasseIndice(1); // Busca a classe que contem o metodo main - Foi a segunda classe a ser carregada

	for (int i = 0; i < main->methods_count; i++) // Percorre o method_info em busca do method main
	{
		nome = main->constant_pool[(main->methods[i].name_index - 1)].info.Utf8.bytes;

		desc = main->constant_pool[(main->methods[i].descriptor_index - 1)].info.Utf8.bytes;

		if (strcmp("main", (char *)nome) == 0) // Se encontrou metodo main retorna uma referencia
		{
			if (strcmp("([Ljava/lang/String;)V", (char *)desc) == 0) // Nome da funcao
			{
				return &(main->methods[i]); // Parametros e Retorno da main
			}
		}
	}

	// Se nao encontra nao possui metodo main na classe carregada
	printf("Metodo main nao encontrado.");
	return NULL;
}

/**
 * @brief Funcao para iniciar um metodo
 * @param metodo method_info* uma referencia ao metodo em questao
 * @param classe classFile* uma referencia a estrutura da classe
 * @return void
 */
void empilhaMetodo(method_info *metodo, classFile *classe)
{
	/**
	 * @brief 1 - Inicializa as instrucoes implementadas pela jvm
	 */
	newInstrucoes();

	/**
	 * @brief 2 - Aloca o frame a ser executado
	 */
	criaFrame(classe->constant_pool, classe, metodo->cd_atrb);
}

/**
 * @brief Percorre os bytecodes do metodo do ultimo frame alocado e
 * executa instrucao a instrucao ate o metodo acabar
 * @param void
 * @return void
 */
void executaFrameCorrente()
{

	// Loop que percorre o frame e executa instrucao a instrucao
	// enquanto houver instrucoes no attributo code
	for (; (frameCorrente->pc) < frameCorrente->code_length;)
	{
		if (frameCorrente == NULL) // Frame corrente == NULL -> nao tem mais frames na pilha
			break;

		// printf("opcode: %d\n",frameCorrente->code[frameCorrente->pc]);
		instrucao[frameCorrente->code[frameCorrente->pc]]();
	}
	desalocaFrame();
}

/**
 * @brief Funcao que recebe um classFile e preenche uma estrutura de um objeto
 * que sera salvo na heap (array)
 * @param classe referencia a um classFile
 * @return referencia a uma estrutura que representa um objeto
 */
objeto *criaObjeto(classFile *classe)
{
	objeto *objeto;

	if (numObjetos == 0)
	{
		heap = calloc(128, sizeof(struct objeto *));
	}

	objeto = calloc(sizeof(objeto), 1); // Aloca espaco
	objeto->classe = classe;						// Inicializa classe do objeto

	// Aloca espaco para os fields
	objeto->campos = calloc(sizeof(uint32_t), classe->fields_count);
	objeto->indiceCampos = calloc(sizeof(uint32_t), classe->fields_count);

	for (int i = 0; i < classe->fields_count; i++) // Preenche o objeto com os indices dos fields.
	{
		objeto->indiceCampos[i] = classe->fields[i].name_index;
	}

	// Coloca no heap
	// heap[numObjetos] = objeto;
	// numObjetos++;
	return objeto;
}

/**
 * @brief Funcao que recebe uma classe de busca um indice para a constant pool
 * e busca o metodo a ser executado. Usado geralmente nos invokes
 * @param indiceClasse classe de indice
 * @param searchClasse classe de busca
 * @param indice indice para constant pool
 * @return referencia a uma estrutura de um metodo
 */
method_info *buscaMetodo(classFile *indiceClasse, classFile *searchClasse, uint16_t indice)
{
	// Busca nome e descricao do metodo pelo indice fornecido
	char *name = retornaNome(indiceClasse, indiceClasse->constant_pool[indice - 1].info.NameAndType.name_index);
	char *desc = retornaNome(indiceClasse, indiceClasse->constant_pool[indice - 1].info.NameAndType.descriptor_index);
	char *searchName;
	char *searchDesc;
	for (int i = 0; i < searchClasse->methods_count; i++)
	{
		searchName = searchClasse->constant_pool[(searchClasse->methods[i].name_index - 1)].info.Utf8.bytes;			 // Busca nome do metodo na searchClasse
		searchDesc = searchClasse->constant_pool[(searchClasse->methods[i].descriptor_index - 1)].info.Utf8.bytes; // Busca descricao do metodo na searchClasse

		if ((strcmp(name, searchName) == 0) && (strcmp(desc, searchDesc) == 0)) // Compara o nome e descricao - Se for igual e o metodo desejado e retorna
		{
			return (searchClasse->methods + i);
		}
	}
}

/**
 * @brief Funcao que recebe um nome e uma descricao de um campo e encontra sua posicao
 * @param className nome da classe que possui o campo
 * @param name nome do campo
 * @param desc descricao do campo
 * @return posicao do campo no fields da classe
 */
int32_t buscaCampo(char *className, char *name, char *desc)
{
	classFile *classe = retornaClasseNome(className); // Obtem classe pelo nome para percorrer seus fields
	uint8_t *searchName;															// Busca nome do campo pelo indice fornecido
	uint8_t *searchDesc;															// Busca descricao do campo pelo indice fornecido
	for (int i = 0; i < classe->fields_count; i++)
	{
		searchName = classe->constant_pool[(classe->fields[i].name_index - 1)].info.Utf8.bytes;				// Busca nome do campo na searchClasse
		searchDesc = classe->constant_pool[(classe->fields[i].descriptor_index - 1)].info.Utf8.bytes; // Busca descricao do campo na searchClasse

		if ((strcmp(name, searchName) == 0) && (strcmp(desc, searchDesc) == 0)) // Compara o nome e descricao - Se for igual e o campo desejado e retorna
		{
			return i;
		}
	}
}

/**
 * @brief Funcao que recebe um nome de classe e a partir desse nome retorna uma
 * referencia da classe com esse nome
 * @param nomeClasse nome da classe buscada
 * @return referencia da classe buscada
 */
classFile *retornaClasseNome(char *nomeClasse)
{
	for (int i = 0; i < area_met.num_classes; i++)
	{
		if (strcmp(nomeClasse, retornaNomeClasse(area_met.array_classes[i])) == 0)
			return area_met.array_classes[i];
	}
	return NULL;
}

/**
 * @brief Funcao que recebe uma classe e um metodo e busca pela quantidade
 * de parametros do metodo presente na descricao dos metodos pelos
 * caracteres especiais (L,B,C,F,I,S,Z,D,J)
 * @param classe referencia a uma classe que contem o metodo
 * @param metodo metodo para acesso a sua descricao
 * @return quantidade de parametros passados para a funcao
 */
int32_t retornaNumeroParametros(classFile *classe, method_info *metodo)
{
	int32_t numeroParametros = 0;
	uint16_t length;
	uint8_t *bytes;

	// Busca o utf8 e o tamanho correspondente da descricao do metodo.
	bytes = classe->constant_pool[(metodo->descriptor_index - 1)].info.Utf8.bytes;
	length = classe->constant_pool[(metodo->descriptor_index - 1)].info.Utf8.length;

	// Percorre o vetor de caracteres em busca dos caracteres especiais.
	// Percorre ate o ) que significa o fim do descriptor.
	int i = 0;
	while (i < length)
	{
		if (bytes[i] == ')')
			break;
		if (bytes[i] == 'L')
		{
			while (bytes[i] != ';')
			{
				i++;
			}
			numeroParametros++;
		}
		else if ((bytes[i] == 'Z') || (bytes[i] == 'S') || (bytes[i] == 'F') || (bytes[i] == 'I') || (bytes[i] == 'C') || (bytes[i] == 'B'))
		{
			numeroParametros++;
		}
		else if ((bytes[i] == 'D') || (bytes[i] == 'J'))
		{
			numeroParametros += 2; // long e Double precisam de dois espacos.
		}
		i++;
	}
	return numeroParametros;
}
