/**
 * @file instrucao.c
 * @section DESCRIPTION
 * Universidade de Brasilia\n
 *
 * Leonardo Pereira Cortes - 200030582\n
 *
 * Software Basico - 2024.1\n
 * Professor: Marcelo Ladeira\n\n
 *
 * Arquivo que contem as instrucoes implementadas pelo programa.
 * Foi usado um vetor de ponteiro para funcoes.
 */

#include "../includes/instrucao.h"
#include "../includes/frame.h"
#include "../includes/carregador.h"
#include "../includes/area_metodos.h"
#include "../includes/metodo.h"

#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#define NULL_REF NULL
#define POS_BAIXA 1
#define POS_ALTA 0

/**
 * @brief Array que guarda as referencias aos vetores alocados
 * Necessario para a instrucao arraylength
 */
vector *arrayVetores = NULL;

/**
 * @brief Guarda a quantidade de arrays alocados para realiar o realloc
 * Necessario para a instrucao arraylength
 */
int32_t qtdArrays = 0;

// Alternativa para memcpy no manipulacao de ponto flutuante -> UNION.

/**
 * @brief Acesso ao frame corrente declarado no modulo frame.h
 */
extern struct frame *frameCorrente;

/**
 * @brief Flag que controla o push na pilha de operandos
 */
int naoEmpilhaFlag = 0;

/**
 * @brief O decodificador eh um array com informacoes das varias instrucoes
 * A partir do opcode da instrucao, pode-se pelo decodificador descobrir o nome e quantos bytes ele ocupa
 */
decodificador dec[NUM_INSTRUCAO];

/**
 * @brief Funcao que atualiza o valor do program counter do frame corrente
 * @param void
 * @return void
 */
void atualizaPc()
{
	inicializa_decodificador(dec);
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;

	for (int8_t i = 0; i < num_bytes + 1; i++) // proxima instrucao
		frameCorrente->pc++;
}

/**
 * @brief A funcao recebe uma referencia para a constant pool e a posicao que se deseja acessar
 * a funcao retorna o indice da CONSTANT_UTF8 associada a CONSTANT da posicao passada na constant pool
 * @param cp uma referencia a constant pool
 * @param pos_pool um indice para a constant pool
 * @return int indice da CONSTANT_UTF8 associada
 */
int obtem_utf_eq(cp_info *cp, int pos_pool)
{
	int tag;
	tag = cp[pos_pool].tag; // pega tag

	if (tag == CONSTANT_Utf8) // se a tag for o de uma UTF8
	{
		return pos_pool;
	}

	// Senao, de acordo com a tag, decide qual sera a proxima posicao da CP que iremos olhar
	switch (tag)
	{
	case CONSTANT_Class:
		return obtem_utf_eq(cp, cp[pos_pool].info.Class.name_index - 1);
	case CONSTANT_String:
		return obtem_utf_eq(cp, cp[pos_pool].info.String.string_index - 1);
	case CONSTANT_Integer:
		return obtem_utf_eq(cp, cp[pos_pool].info.String.string_index - 1);
	case CONSTANT_Float:
		return obtem_utf_eq(cp, cp[pos_pool].info.String.string_index - 1);
	}
}

/**
 * @brief Funcao que aponta para uma implementacao de cada instrucao de acordo com o opcode fornecido
 * @param void
 * @return void
 */
void newInstrucoes()
{
	instrucao[0] = nop;
	instrucao[1] = aconst_null;
	instrucao[2] = iconst_m1;
	instrucao[3] = iconst_0;
	instrucao[4] = iconst_1;
	instrucao[5] = iconst_2;
	instrucao[6] = iconst_3;
	instrucao[7] = iconst_4;
	instrucao[8] = iconst_5;
	instrucao[9] = lconst_0;
	instrucao[10] = lconst_1;
	instrucao[11] = fconst_0;
	instrucao[12] = fconst_1;
	instrucao[13] = fconst_2;
	instrucao[14] = dconst_0;
	instrucao[15] = dconst_1;
	instrucao[16] = bipush;
	instrucao[17] = sipush;
	instrucao[18] = ldc;
	instrucao[19] = ldc_w;
	instrucao[20] = ldc2_w;
	instrucao[21] = iload;
	instrucao[22] = lload;
	instrucao[23] = fload;
	instrucao[24] = dload;
	instrucao[25] = aload;
	instrucao[26] = iload_0;
	instrucao[27] = iload_1;
	instrucao[28] = iload_2;
	instrucao[29] = iload_3;
	instrucao[30] = lload_0;
	instrucao[31] = lload_1;
	instrucao[32] = lload_2;
	instrucao[33] = lload_3;
	instrucao[34] = fload_0;
	instrucao[35] = fload_1;
	instrucao[36] = fload_2;
	instrucao[37] = fload_3;
	instrucao[38] = dload_0;
	instrucao[39] = dload_1;
	instrucao[40] = dload_2;
	instrucao[41] = dload_3;
	instrucao[42] = aload_0;
	instrucao[43] = aload_1;
	instrucao[44] = aload_2;
	instrucao[45] = aload_3;
	instrucao[46] = iaload;
	instrucao[47] = laload;
	instrucao[48] = faload;
	instrucao[49] = daload;
	instrucao[50] = aaload;
	instrucao[51] = baload;
	instrucao[52] = caload;
	instrucao[53] = saload;
	instrucao[54] = istore;
	instrucao[55] = lstore;
	instrucao[56] = fstore;
	instrucao[57] = dstore;
	instrucao[58] = astore;
	instrucao[59] = istore_0;
	instrucao[60] = istore_1;
	instrucao[61] = istore_2;
	instrucao[62] = istore_3;
	instrucao[63] = lstore_0;
	instrucao[64] = lstore_1;
	instrucao[65] = lstore_2;
	instrucao[66] = lstore_3;
	instrucao[67] = fstore_0;
	instrucao[68] = fstore_1;
	instrucao[69] = fstore_2;
	instrucao[70] = fstore_3;
	instrucao[71] = dstore_0;
	instrucao[72] = dstore_1;
	instrucao[73] = dstore_2;
	instrucao[74] = dstore_3;
	instrucao[75] = astore_0;
	instrucao[76] = astore_1;
	instrucao[77] = astore_2;
	instrucao[78] = astore_3;
	instrucao[79] = iastore;
	instrucao[80] = lastore;
	instrucao[81] = fastore;
	instrucao[82] = dastore;
	instrucao[83] = aastore;
	instrucao[84] = bastore;
	instrucao[85] = castore;
	instrucao[86] = sastore;
	instrucao[87] = pop;
	instrucao[88] = pop2;
	instrucao[89] = dup;
	instrucao[90] = dup2_x1;
	instrucao[91] = dup2_x2;
	instrucao[92] = dup2;
	instrucao[93] = dup2_x1;
	instrucao[94] = dup2_x2;
	instrucao[95] = swap;
	instrucao[96] = iadd;
	instrucao[97] = ladd;
	instrucao[98] = fadd;
	instrucao[99] = dadd;
	instrucao[100] = isub;
	instrucao[101] = lsub;
	instrucao[102] = fsub;
	instrucao[103] = dsub;
	instrucao[104] = imul;
	instrucao[105] = lmul;
	instrucao[106] = fmul;
	instrucao[107] = dmul;
	instrucao[108] = idiv;
	instrucao[109] = ins_ldiv;
	instrucao[110] = fdiv;
	instrucao[111] = ddiv;
	instrucao[112] = irem;
	instrucao[113] = lrem;
	instrucao[114] = frem;
	instrucao[115] = _drem;
	instrucao[116] = ineg;
	instrucao[117] = lneg;
	instrucao[118] = fneg;
	instrucao[119] = dneg;
	instrucao[120] = ishl;
	instrucao[121] = lshl;
	instrucao[122] = ishr;
	instrucao[123] = lshr;
	instrucao[124] = iushr;
	instrucao[125] = lushr;
	instrucao[126] = iand;
	instrucao[127] = land;
	instrucao[128] = ior;
	instrucao[129] = lor;
	instrucao[130] = ixor;
	instrucao[131] = lxor;
	instrucao[132] = iinc;
	instrucao[133] = i2l;
	instrucao[134] = i2f;
	instrucao[135] = i2d;
	instrucao[136] = l2i;
	instrucao[137] = l2f;
	instrucao[138] = l2d;
	instrucao[139] = f2i;
	instrucao[140] = f2l;
	instrucao[141] = f2d;
	instrucao[142] = d2i;
	instrucao[143] = d2l;
	instrucao[144] = d2f;
	instrucao[145] = i2b;
	instrucao[146] = i2c;
	instrucao[147] = i2s;
	instrucao[148] = lcmp;
	instrucao[149] = fcmpl;
	instrucao[150] = fcmpg;
	instrucao[151] = dcmpl;
	instrucao[152] = dcmpg;
	instrucao[153] = ifeq;
	instrucao[154] = ifne;
	instrucao[155] = iflt;
	instrucao[156] = ifge;
	instrucao[157] = ifgt;
	instrucao[158] = ifle;
	instrucao[159] = if_icmpeq;
	instrucao[160] = if_icmpne;
	instrucao[161] = if_icmplt;
	instrucao[162] = if_icmpge;
	instrucao[163] = if_icmpgt;
	instrucao[164] = if_icmple;
	instrucao[165] = if_acmpeq;
	instrucao[166] = if_acmpne;
	instrucao[167] = ins_goto;
	instrucao[168] = jsr;
	instrucao[169] = ret;
	instrucao[170] = tableswitch;
	instrucao[171] = lookupswitch;
	instrucao[172] = ireturn;
	instrucao[173] = lreturn;
	instrucao[174] = freturn;
	instrucao[175] = dreturn;
	instrucao[176] = areturn;
	instrucao[177] = ins_return;
	instrucao[178] = getstatic;
	instrucao[179] = putstatic;
	instrucao[180] = getfield;
	instrucao[181] = putfield;
	instrucao[182] = invokevirtual;
	instrucao[183] = invokespecial;
	instrucao[184] = invokestatic;
	instrucao[185] = invokeinterface;
	instrucao[187] = ins_new;
	instrucao[188] = newarray;
	instrucao[189] = anewarray;
	instrucao[190] = arraylength;
	instrucao[192] = checkcast;
	instrucao[193] = instanceof ;
	instrucao[196] = wide;
	instrucao[197] = multianewarray;
	instrucao[198] = ifnull;
	instrucao[199] = ifnonnull;
	instrucao[200] = goto_w;
	instrucao[201] = jsr_w;
}

/**
 * Implementacao de cada instrucao
 */

/**
 * @brief Funcao que nao realiza nada na pilha de operandos nem no array de var local
 * Somente pula para a proxima instrucao
 * @param void
 * @return void
 */
void nop()
{
	frameCorrente->pc++; // pula para proxima instrucao, atualizando pc
}

/**
 * @brief Funcao que poe o valor a referencia null na pilha de operandos
 * @param void
 * @return void
 */
void aconst_null()
{
	push((int32_t)NULL_REF); // poe a refererencia null na pilha
	frameCorrente->pc++;		 // atualiza pc
}

/**
 * @brief Funcao que poe a constante inteira -1 na pilha de operandos
 * @param void
 * @return void
 */
void iconst_m1()
{
	char *tipo = "I";
	tipoGlobal = tipo;
	push(-1);						 // poe -1 na pilha de operandos
	frameCorrente->pc++; // atualiza pc
}

/**
 * @brief Funcao que empilha 0 na pilha de operandos
 * @param void
 * @return void
 */
void iconst_0()
{
	char *tipo = "I";
	tipoGlobal = tipo;
	push((int32_t)0); // poe 0 na pilha de operandos
	atualizaPc();
}

/**
 * @brief Funcao que empilha 1 na pilha de operandos
 * @param void
 * @return void
 */
void iconst_1()
{
	char *tipo = "I";
	tipoGlobal = tipo;
	push(1);						 // poe 1 na pilha de operandos
	frameCorrente->pc++; // atualiza pc
}

/**
 * @brief Funcao que empilha 2 na pilha de operandos
 * @param void
 * @return void
 */
void iconst_2()
{
	char *tipo = "I";
	tipoGlobal = tipo;
	push(2);						 // poe 2 na pilha de operandos
	frameCorrente->pc++; // atualiza pc
}

/**
 * @brief Funcao que empilha 3 na pilha de operandos
 * @param void
 * @return void
 */
void iconst_3()
{
	char *tipo = "I";
	tipoGlobal = tipo;
	push(3);						 // poe 3 na pilha de operandos
	frameCorrente->pc++; // atualiza pc
}

/**
 * @brief Funcao que empilha 4 na pilha de operandos
 * @param void
 * @return void
 */
void iconst_4()
{
	char *tipo = "I";
	tipoGlobal = tipo;
	push(4);						 // poe 4 na pilha de operandos
	frameCorrente->pc++; // atualiza pc
}

/**
 * @brief Funcao que empilha 5 na pilha de operandos
 * @param void
 * @return void
 */
void iconst_5()
{
	char *tipo = "I";
	tipoGlobal = tipo;
	push(5);						 // poe 5 na pilha de operandos
	frameCorrente->pc++; // atualiza pc
}

/**
 * @brief a funcao coloca a constante long 0 na pilha de operandos (ocupa 2 espacos na pilha)
 * @param void
 * @return void
 */
void lconst_0()
{
	char *tipo = "L";
	tipoGlobal = tipo;
	int64_t long0 = 0;
	int32_t parte_alta;
	int32_t parte_baixa;

	parte_alta = long0 >> 32;					// pega parte alta do long
	parte_baixa = long0 & 0xffffffff; // pega parte baixa do long

	push(parte_alta);		 // pela convencao, empilha a parte alta primeiro
	push(parte_baixa);	 //  empilha a parte baixa depois
	frameCorrente->pc++; // atualiza pc
}

/**
 * @brief a funcao coloca a constante long 1 na pilha de operandos
 * ocupa 2 espacos na pilha
 * @param void
 * @return void
 */
void lconst_1()
{
	char *tipo = "L";
	tipoGlobal = tipo;
	int64_t long1 = 1;
	int32_t parte_alta;
	int32_t parte_baixa;

	parte_alta = long1 >> 32;					// pega parte alta do long
	parte_baixa = long1 & 0xffffffff; // pega parte baixa do long

	push(parte_alta);		 // pela convencao, empilha a parte alta primeiro
	push(parte_baixa);	 // empilha a parte baixa depois
	frameCorrente->pc++; // atualiza pc
}

/**
 * @brief Funcao que coloca 0.0 na pilha
 * @param void
 * @return void
 */
void fconst_0()
{
	char *tipo = "F";
	tipoGlobal = tipo;
	float valF = 0.0; // Float com valor zero para ser empilhado

	int32_t *valPilha;														 // Auxiliar para utilizar o memcpy e nao perder precisao com cast
	valPilha = (int32_t *)malloc(sizeof(int32_t)); // Aloca mem para int32

	// Importante - copia bytes de um float para um int32 para empilhar na forma correta.
	// Ao desempilhar realiza Memcpy de volta para um float
	memcpy(valPilha, &valF, sizeof(int32_t));

	push(*valPilha); // Empilha float na forma de int32 para se adequar ao tipo da pilha
	atualizaPc();
}

/**
 * @brief Funcao que coloca 1.0 na pilha
 * @param void
 * @return void
 */
void fconst_1()
{
	char *tipo = "F";
	tipoGlobal = tipo;
	float valF = 1.0; // Float com valor zero para ser empilhado

	int32_t *valPilha;														 // Auxiliar para utilizar o memcpy e nao perder precisao com cast
	valPilha = (int32_t *)malloc(sizeof(int32_t)); // Aloca mem para int32

	// Importante - copia bytes de um float para um int32 para empilhar na forma correta.
	// Ao desempilhar realiza Memcpy de volta para um float
	memcpy(valPilha, &valF, sizeof(int32_t));

	push(*valPilha); // Empilha float na forma de int32 para se adequar ao tipo da pilha
	atualizaPc();
}

/**
 * @brief Funcao que coloca 2.0 na pilha
 * @param void
 * @return void
 */
void fconst_2()
{
	char *tipo = "F";
	tipoGlobal = tipo;
	float valF = 2.0; // Float com valor zero para ser empilhado

	int32_t *valPilha;														 // Auxiliar para utilizar o memcpy e nao perder precisao com cast
	valPilha = (int32_t *)malloc(sizeof(int32_t)); // Aloca mem para int32

	// Importante - copia bytes de um float para um int32 para empilhar na forma correta.
	// Ao desempilhar realiza Memcpy de volta para um float
	memcpy(valPilha, &valF, sizeof(int32_t));

	push(*valPilha); // Empilha float na forma de int32 para se adequar ao tipo da pilha
	atualizaPc();
}

/**
 * @brief funcao que empilha o double 0.0 na pilha
 * @param void
 * @return void
 */
void dconst_0()
{
	char *tipo = "D";
	tipoGlobal = tipo;

	double double0 = 0.0;
	int64_t temp;
	int32_t parte_alta;
	int32_t parte_baixa;

	memcpy(&temp, &double0, sizeof(int64_t)); // copia valor de double para o int temp

	parte_alta = temp >> 32;				 // divide temp em parte alta
	parte_baixa = temp & 0xffffffff; // e parte baixa

	push(parte_alta);	 // empilha a parte alta primeiro
	push(parte_baixa); // empilha depois a baixa

	frameCorrente->pc++; // atualiza pc
}

/**
 * @brief funcao que empilha o double 1.0 na pilha
 * @param void
 * @return void
 */
void dconst_1()
{
	char *tipo = "D";
	tipoGlobal = tipo;

	double double1 = 1.0;
	int64_t temp;
	int32_t parte_alta;
	int32_t parte_baixa;

	memcpy(&temp, &double1, sizeof(int64_t)); // copia valor de double para o int temp

	parte_alta = temp >> 32;				 // divide temp em parte alta
	parte_baixa = temp & 0xffffffff; //  e parte baixa

	push(parte_alta);	 // empilha a parte alta primeiro
	push(parte_baixa); // empilha depois a baixa

	// atualiza pc
	frameCorrente->pc++;
}

/**
 * @brief Acessa um parametro(8 bits) da instrucao em empilha na pilha de operandos
 * @param void
 * @return void
 */
void bipush()
{
	int8_t argumento = (int8_t)frameCorrente->code[frameCorrente->pc + 1];
	push((int32_t)argumento);
	atualizaPc();
}

/**
 * @brief le dois bytes e poe resultado da concantenacao deles na pilha
 * @param void
 * @return void
 */
void sipush()
{
	int32_t byte1, byte2;
	int32_t valor;
	int16_t short_temp;

	byte1 = frameCorrente->code[(frameCorrente->pc + 1)]; // pega primeiro byte
	byte2 = frameCorrente->code[(frameCorrente->pc + 2)]; // pega segundo byte

	short_temp = (byte1 << 8) + byte2;
	valor = (int32_t)short_temp; // obtem short

	push(valor); // poe valor no stack de operandos
	atualizaPc();
}

/**
 * @brief a funcao coloca um item da run-time constant pool obtido
 * a partir de um indice fornecido na instrucao na pilha
 * @param void
 * @return void
 */
void ldc()
{
	uint32_t indice;
	tipoGlobal = NULL;

	indice = frameCorrente->code[frameCorrente->pc + 1]; // pega indice

	// se o indice para a constant pool for para um int ou float
	if (frameCorrente->constant_pool[indice - 1].tag == CONSTANT_Float ||
			frameCorrente->constant_pool[indice - 1].tag == CONSTANT_Integer)
	{
		// empilha valor correto
		if (frameCorrente->constant_pool[indice - 1].tag == CONSTANT_Float)
		{
			push(frameCorrente->constant_pool[indice - 1].info.Float.bytes);
		}
		else
		{
			push(frameCorrente->constant_pool[indice - 1].info.Integer.bytes);
		}
	}

	// se o indice para a constant pool for para uma string
	else if (frameCorrente->constant_pool[indice - 1].tag == CONSTANT_String)
	{
		uint32_t indice_utf;
		indice_utf = obtem_utf_eq(frameCorrente->constant_pool, indice - 1);
		push(indice_utf);
	}

	// se o indice para a constant pool for uma referencia a uma classe
	else if (frameCorrente->constant_pool[indice - 1].tag == CONSTANT_String)
	{
		// poe referencia para a classe na constant pool
		printf("erro - funcionalidade nao implementada\n");
		exit(1);
	}

	// se nao for nenhum dos acima, reporta erro e sai
	else
	{
		printf("erro na instrucao ldc\n");
		exit(1);
	}

	atualizaPc();
}

/**
 * @brief a funcao coloca um item da run-time constant pool na pilha
 * Semelhante a ldc, mas o indice lido eh um numero de 16 bits ao inves de 8
 * @param void
 * @return void
 */
void ldc_w()
{
	uint32_t indice;

	inicializa_decodificador(dec);
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;

	indice = (frameCorrente->code[frameCorrente->pc + 1] << 8 + frameCorrente->code[frameCorrente->pc + 2]); // pega indice

	// se o indice para a constant pool for para um int ou float
	if (frameCorrente->constant_pool[indice - 1].tag == CONSTANT_Float ||
			frameCorrente->constant_pool[indice - 1].tag == CONSTANT_Integer)
	{
		// empilha valor correto
		if (frameCorrente->constant_pool[indice - 1].tag == CONSTANT_Float)
		{
			push(frameCorrente->constant_pool[indice - 1].info.Float.bytes);
		}
		else
		{
			push(frameCorrente->constant_pool[indice - 1].info.Integer.bytes);
		}
	}

	// se o indice para a constant pool for para uma string
	else if (frameCorrente->constant_pool[indice - 1].tag == CONSTANT_String)
	{
		uint32_t indice_utf;
		indice_utf = obtem_utf_eq(frameCorrente->constant_pool, indice - 1);
		push(indice_utf);
	}

	// se o indice para a constant pool for uma referencia a uma classe
	else if (frameCorrente->constant_pool[indice - 1].tag == CONSTANT_String)
	{
		// poe referencia para a classe na constant pool
		// TODO Resolve nome da classe
	}

	// se nao for nenhum dos acima, reporta erro e sai
	else
	{
		printf("erro na instrucao ldc\n");
		exit(1);
	}

	// atualiza proxima instrucao
	for (int8_t i = 0; i < num_bytes + 1; i++)
		frameCorrente->pc++;
}

/**
 * @brief Acessa a constant pool num campo de 64 bits e coloca na pilha
 * @param void
 * @return void
 */
void ldc2_w()
{
	uint8_t indice = frameCorrente->code[frameCorrente->pc + 2];	// Pega indice presente na instrucao para acesso a constant pool
	uint8_t tag = (frameCorrente->constant_pool[indice - 1]).tag; // Pega tag da posicao da constant pool dada pelo indice (pode ser ou long ou double)

	// long
	if (tag == 5)
	{
		uint32_t alta = frameCorrente->constant_pool[indice - 1].info.Long.high_bytes;
		uint32_t baixa = frameCorrente->constant_pool[indice - 1].info.Long.low_bytes;
		push(alta);
		push(baixa);
	}

	// Se tag eh 6 (double), acessa high bytes e low bytes e empilha
	if (tag == 6)
	{
		uint32_t alta = frameCorrente->constant_pool[indice - 1].info.Double.high_bytes;
		uint32_t baixa = frameCorrente->constant_pool[indice - 1].info.Double.low_bytes;
		push(alta);
		push(baixa);
	}

	atualizaPc();
	foi_lneg = false;
}

/**
 * LOADS
 */

/**
 * @brief funcao carrega um inteira do array de variaveis locais na pilha de operandos
 * @param void
 * @return void
 */
void iload()
{
	char *tipo = "I";
	tipoGlobal = tipo;

	int32_t argumento = (int32_t)frameCorrente->code[frameCorrente->pc + 1];
	int32_t aux = frameCorrente->fields[argumento];
	push(aux);

	atualizaPc();
}

/**
 * @brief a funcao carrega um long do array de var locais a pilha de operandos
 * @param void
 * @return void
 */
void lload()
{
	char *tipo = "L";
	tipoGlobal = tipo;
	int32_t indice;
	int32_t parte_alta, parte_baixa;

	indice = frameCorrente->code[frameCorrente->pc + 1]; // pega indice

	parte_alta = frameCorrente->fields[indice + POS_ALTA];
	push(parte_alta); // empilha a parte alta - por convencao eh empilhada primeiro

	parte_baixa = frameCorrente->fields[indice + POS_BAIXA];
	push(parte_baixa); // empilha a parte baixa - por convencao eh emprilhada depois

	atualizaPc();
}

/**
 * @brief a funcao carrega um float no array de variaveis locais da pilha
 * @param void
 * @return void
 */
void fload()
{
	char *tipo = "F";
	tipoGlobal = tipo;
	int32_t indice, valor;

	indice = frameCorrente->code[frameCorrente->pc + 1]; // pega indice

	valor = frameCorrente->fields[indice];
	push(valor); // empilha

	atualizaPc();
}

/**
 * @brief a funcao carrega um double no array de variaveis locais da pilha
 * @param void
 * @return void
 */
void dload()
{
	int32_t indice;
	int32_t parte_alta, parte_baixa;
	char *tipo = "D";
	tipoGlobal = tipo;

	indice = frameCorrente->code[frameCorrente->pc + 1]; // pega indice

	parte_alta = frameCorrente->fields[indice + POS_ALTA];
	push(parte_alta); // empilha a parte alta - por convencao eh empilhada primeiro

	parte_baixa = frameCorrente->fields[indice + POS_BAIXA];
	push(parte_baixa); // empilha a parte baixa - por convencao eh emprilhada depois

	atualizaPc();
}

/**
 * @brief a funcao carrega uma referencia do array de variaveis locais da pilha
 * @param void
 * @return void
 */
void aload()
{
	int32_t indice, valor;
	indice = frameCorrente->code[frameCorrente->pc + 1]; // pega indice

	valor = frameCorrente->fields[indice];
	push(valor); // empilha

	atualizaPc();
}

/**
 * @brief a funcao carrega o int na posicao 0 do array de variaveis locais para a pilha de operandos
 * @param void
 * @return void
 */
void iload_0()
{
	char *tipo = "I";
	tipoGlobal = tipo;
	int32_t valor;

	valor = frameCorrente->fields[0]; // pega valor do array de var local na posicao 0
	push(valor);											// poe valor na pilha de operandos

	atualizaPc();
}

/**
 * @brief a funcao carrega o int na posicao 1 do array de variaveis locais para a pilha de operandos
 * @param void
 * @return void
 */
void iload_1()
{
	char *tipo = "I";
	tipoGlobal = tipo;
	int32_t valor;

	valor = frameCorrente->fields[1]; // pega valor do array de var local na posicao 1
	push(valor);											// poe valor na pilha de operandos

	atualizaPc();
}

/**
 * @brief a funcao carrega o int na posicao 2 do array de variaveis locais para a pilha de operandos
 * @param void
 * @return void
 */
void iload_2()
{
	char *tipo = "I";
	tipoGlobal = tipo;
	int32_t valor;

	valor = frameCorrente->fields[2]; // pega valor do array de var local na posicao 2
	push(valor);											// poe valor na pilha de operandos

	atualizaPc();
}

/**
 * @brief a funcao carrega o int na posicao 3 do array de variaveis locais para a pilha de operandos
 * @param void
 * @return void
 */
void iload_3()
{
	int32_t valor;
	char *tipo = "I";
	tipoGlobal = tipo;

	valor = frameCorrente->fields[3]; // pega valor do array de var local na posicao 3
	push(valor);											// poe valor na pilha de operandos

	atualizaPc();
}

/**
 * @brief a funcao carrega o long da posicao 0/1 do array de variaveis locais na pilha de operandos
 * @param void
 * @return void
 **/
void lload_0()
{

	char *tipo = "L";
	tipoGlobal = tipo;
	int32_t indice;
	int32_t parte_alta, parte_baixa;
	indice = 0; // pega indice

	parte_alta = frameCorrente->fields[indice + POS_ALTA];
	push(parte_alta); // empilha a parte alta - por convencao eh empilhada primeiro

	parte_baixa = frameCorrente->fields[indice + POS_BAIXA];
	push(parte_baixa); // empilha a parte baixa - por convencao eh emprilhada depois

	atualizaPc();
}

/**
 * @brief a funcao carrega o long da posicao 1/2 do array de variaveis locais na pilha de operandos
 * @param void
 * @return void
 */
void lload_1()
{
	int32_t indice;
	int32_t parte_alta, parte_baixa;
	char *tipo = "L";
	tipoGlobal = tipo;
	indice = 1; // pega indice

	parte_alta = frameCorrente->fields[indice + POS_ALTA];
	push(parte_alta); // empilha a parte alta - por convencao eh empilhada primeiro

	parte_baixa = frameCorrente->fields[indice + POS_BAIXA];
	push(parte_baixa); // empilha a parte baixa - por convencao eh emprilhada depois

	atualizaPc();
}

/**
 * @brief a funcao carrega o long da posicao 2/3 do array de variaveis locais na pilha de operandos
 * @param void
 * @return void
 */
void lload_2()
{

	char *tipo = "L";
	tipoGlobal = tipo;
	int32_t indice;
	int32_t parte_alta, parte_baixa;
	indice = 2; // pega indice

	parte_alta = frameCorrente->fields[indice + POS_ALTA];
	push(parte_alta); // empilha a parte alta - por convencao eh empilhada primeiro

	parte_baixa = frameCorrente->fields[indice + POS_BAIXA];
	push(parte_baixa); // empilha a parte baixa - por convencao eh emprilhada depois

	atualizaPc();
}

/**
 * @brief a funcao carrega o long da posicao 3/4 do array de variaveis locais na pilha de operandos
 * @param void
 * @return void
 */
void lload_3()
{
	char *tipo = "L";
	tipoGlobal = tipo;
	int32_t indice;
	int32_t parte_alta, parte_baixa;
	indice = 3; // pega indice

	parte_alta = frameCorrente->fields[indice + POS_ALTA];
	push(parte_alta); // empilha a parte alta - por convencao eh empilhada primeiro

	parte_baixa = frameCorrente->fields[indice + POS_BAIXA];
	push(parte_baixa); // empilha a parte baixa - por convencao eh emprilhada depois

	atualizaPc();
}

/**
 * @brief a funcao carrega o float da posicao 0 do array de variaveis locais na pilha de operandos
 * @param void
 * @return void
 */
void fload_0()
{

	char *tipo = "F";
	tipoGlobal = tipo;
	int32_t indice, valor;
	indice = 0; // pega indice

	valor = frameCorrente->fields[indice];
	push(valor); // empilha

	atualizaPc();
}

/**
 * @brief a funcao carrega o float da posicao 1 do array de variaveis locais na pilha de operandos
 * @param void
 * @return void
 */
void fload_1()
{
	char *tipo = "F";
	tipoGlobal = tipo;
	int32_t indice, valor;
	indice = 1; // pega indice

	valor = frameCorrente->fields[indice];
	push(valor); // empilha

	atualizaPc();
}

/**
 * @brief a funcao carrega o float da posicao 2 do array de variaveis locais na pilha de operandos
 * @param void
 * @return void
 */
void fload_2()
{
	char *tipo = "F";
	tipoGlobal = tipo;
	int32_t indice, valor;
	indice = 2; // pega indice

	valor = frameCorrente->fields[indice];
	push(valor); // empilha

	atualizaPc();
}

/**
 * @brief a funcao carrega o float da posicao 3 do array de variaveis locais na pilha de operandos
 * @param void
 * @return void
 */
void fload_3()
{
	char *tipo = "F";
	tipoGlobal = tipo;
	int32_t indice, valor;
	indice = 3; // pega indice

	valor = frameCorrente->fields[indice];
	push(valor); // empilha

	atualizaPc();
}

/**
 * @brief a funcao carrega o double da posicao 0/1 do array de variaveis locais na pilha de operandos
 * @param void
 * @return void
 */
void dload_0()
{

	char *tipo = "D";
	tipoGlobal = tipo;
	int32_t indice;
	int32_t parte_alta, parte_baixa;
	indice = 0; // pega indice

	parte_alta = frameCorrente->fields[indice + POS_ALTA];
	push(parte_alta); // empilha a parte alta - por convencao eh empilhada primeiro

	parte_baixa = frameCorrente->fields[indice + POS_BAIXA];
	push(parte_baixa); // empilha a parte baixa - por convencao eh emprilhada depois

	atualizaPc();
}

/**
 * @brief a funcao carrega o double da posicao 1/2 do array de variaveis locais na pilha de operandos
 * @param void
 * @return void
 */
void dload_1()
{
	int32_t indice;
	int32_t parte_alta, parte_baixa;
	char *tipo = "D";
	tipoGlobal = tipo;
	indice = 1; // pega indice

	parte_alta = frameCorrente->fields[indice + POS_ALTA];
	push(parte_alta); // empilha a parte alta - por convencao eh empilhada primeiro

	parte_baixa = frameCorrente->fields[indice + POS_BAIXA];
	push(parte_baixa); // empilha a parte baixa - por convencao eh emprilhada depois

	atualizaPc();
}

/**
 * @brief a funcao carrega o double da posicao 2/3 do array de variaveis locais na pilha de operandos
 * @param void
 * @return void
 */
void dload_2()
{
	int32_t indice;
	int32_t parte_alta, parte_baixa;
	char *tipo = "D";
	tipoGlobal = tipo;
	indice = 2; // pega indice

	parte_alta = frameCorrente->fields[indice + POS_ALTA];
	push(parte_alta); // empilha a parte alta - por convencao eh empilhada primeiro

	parte_baixa = frameCorrente->fields[indice + POS_BAIXA];
	push(parte_baixa); // empilha a parte baixa - por convencao eh emprilhada depois

	atualizaPc();
}

/**
 * @brief a funcao carrega o double da posicao 3/4 do array de variaveis locais na pilha de operandos
 * @param void
 * @return void
 */
void dload_3()
{
	int32_t indice;
	int32_t parte_alta, parte_baixa;
	char *tipo = "D";
	tipoGlobal = tipo;
	indice = 3; // pega indice

	parte_alta = frameCorrente->fields[indice + POS_ALTA];
	push(parte_alta); // empilha a parte alta - por convencao eh empilhada primeiro

	parte_baixa = frameCorrente->fields[indice + POS_BAIXA];
	push(parte_baixa); // empilha a parte baixa - por convencao eh emprilhada depois

	atualizaPc();
}

/**
 * @brief Acessa posicao 0 do array de var local e empilha na pilha de operandos
 * @param void
 * @return void
 */
void aload_0()
{
	push(frameCorrente->fields[0]); // Empilha a posicao 0 do vetor de variaveis locais
	atualizaPc();
}

/**
 * @brief a funcao acessa a posicao 1 do array de var local e empilha o conteudo na pilha de operandos
 * @param void
 * @return voi
 */
void aload_1()
{
	int32_t indice, valor;
	indice = 1; // pega indice

	valor = frameCorrente->fields[indice];
	push(valor); // empilha
	atualizaPc();
}

/**
 * @brief a funcao acessa a posicao 2 do array de var local e empilha o conteudo na pilha de operandos
 * @param void
 * @return voi
 */
void aload_2()
{
	int32_t indice, valor;
	indice = 2; // pega indice

	valor = frameCorrente->fields[indice];
	push(valor); // empilha
	atualizaPc();
}
/**
 * @brief a funcao acessa a posicao 3 do array de var local e empilha o conteudo na pilha de operandos
 * @param void
 * @return voi
 */
void aload_3()
{
	int32_t indice, valor;
	indice = 3; // pega indice

	valor = frameCorrente->fields[indice];
	push(valor); // empilha
	atualizaPc();
}

/**
 * @brief Obtem da pilha o indice a ser acessado no vetor, obtem da pilha
 * a referencia ao vetor previamente alocado. Acessa o vetor na
 * posicao do indice e empilha o valor correspondente
 * @param void
 * @return void
 */
void iaload()
{
	int32_t *referencia;							// Referncia para o vetor obtida da pilha
	int32_t indice = pop_op();				// Pega indice da pilha de operandos
	referencia = (int32_t *)pop_op(); // Pega referencia para o array alocado
	push(referencia[indice]);					// Acessa o array no indice e empilha o valor
	atualizaPc();
}

/**
 * @brief Obtem da pilha o indice a ser acessado no vetor, obtem da pilha
 * a referencia ao vetor previamente alocado. Acessa o vetor na
 * posicao do indice e empilha o valor correspondente
 * @param void
 * @return void
 */
void laload()
{
	static int16_t countPos = 0;
	char *tipo = "L";
	tipoGlobal = tipo;
	int32_t indice = pop_op(); // Obtem indice de acesso ao array
	int32_t *referencia;			 // Referencia para o vetor obtida da pilha
	referencia = (int32_t *)pop_op();

	push(referencia[countPos + indice + 1]); // Empilha parte baixa
	push(referencia[countPos + indice]);		 // Empilha parte baixa
	countPos += 2;
	atualizaPc();
}

/**
 * @brief Obtem da pilha o indice a ser acessado no vetor, obtem da pilha
 * a referencia ao vetor previamente alocado. Acessa o vetor na
 * posicao do indice e empilha o valor correspondente
 * @param void
 * @return void
 */
void faload()
{
	char *tipo = "F";
	tipoGlobal = tipo;
	int32_t *referencia;							// Referncia para o vetor obtida da pilha
	int32_t indice = pop_op();				// Pega indice da pilha de operandos
	referencia = (int32_t *)pop_op(); // Pega referencia para o array alocado

	int32_t valPilha;
	memcpy(&valPilha, &((float *)referencia)[indice], sizeof(int32_t)); // Acessa o array no indice
	push(valPilha);																											// Empilha o valor

	atualizaPc();
}

/**
 * @brief Obtem da pilha o indice a ser acessado no vetor, obtem da pilha
 * a referencia ao vetor previamente alocado. Acessa o vetor na
 * posicao do indice e empilha o valor correspondente
 * @param void
 * @return void
 */
void daload()
{
	static int16_t countPos = 0;
	char *tipo = "D";
	tipoGlobal = tipo;
	int32_t indice = pop_op(); // Obtem indice de acesso ao array
	int32_t *referencia;			 // Referencia para o vetor obtida da pilha
	referencia = (int32_t *)pop_op();

	push(referencia[countPos + indice + 1]); // Empilha parte alta
	push(referencia[countPos + indice]);		 // Empilha parte baixa
	countPos += 2;
	atualizaPc();
}

/**
 * @brief Obtem da pilha o indice a ser acessado no vetor, obtem da pilha
 * a referencia ao vetor previamente alocado. Acessa o vetor na
 * posicao do indice e empilha o valor correspondente
 * @param void
 * @return void
 */
void aaload()
{
	int32_t *referencia;							// Referncia para o vetor obtida da pilha
	int32_t indice = pop_op();				// Pega indice da pilha de operandos
	referencia = (int32_t *)pop_op(); // Pega referencia para o array alocado
	push(referencia[indice]);					// Acessa o array no indice e empilha o valor
	atualizaPc();
}

/**
 * @brief Obtem da pilha o indice a ser acessado no vetor, obtem da pilha
 * a referencia ao vetor previamente alocado. Acessa o vetor na
 * posicao do indice e empilha o valor correspondente
 * @param void
 * @return void
 */
void baload()
{
	int32_t *referencia;													 // Referncia para o vetor obtida da pilha
	int32_t indice = pop_op();										 // Pega indice da pilha de operandos
	referencia = (int32_t *)pop_op();							 // Pega referencia para o array alocado
	int8_t *binary = (int8_t *)referencia[indice]; // Acessa o array no indice
	push((int32_t)binary);												 // Empilha o valor
	atualizaPc();
}

/**
 * @brief Obtem da pilha o indice a ser acessado no vetor, obtem da pilha
 * a referencia ao vetor previamente alocado. Acessa o vetor na
 * posicao do indice e empilha o valor correspondente
 * @param void
 * @return void
 */
void caload()
{
	char *tipo = "C";
	tipoGlobal = tipo;
	int32_t *referencia;														 // Referncia para o vetor obtida da pilha
	int32_t indice = pop_op();											 // Pega indice da pilha de operandos
	referencia = (int32_t *)pop_op();								 // Pega referencia para o array alocado
	int16_t *binary = (int16_t *)referencia[indice]; // Acessa o array no indice
	push((int32_t)binary);													 // Empilha o valor
	atualizaPc();
}

/**
 * @brief Obtem da pilha o indice a ser acessado no vetor, obtem da pilha
 * a referencia ao vetor previamente alocado. Acessa o vetor na
 * posicao do indice e empilha o valor correspondente
 * @param void
 * @return void
 */
void saload()
{
	int32_t *referencia;														 // Referncia para o vetor obtida da pilha
	int32_t indice = pop_op();											 // Pega indice da pilha de operandos
	referencia = (int32_t *)pop_op();								 // Pega referencia para o array alocado
	int16_t *binary = (int16_t *)referencia[indice]; // Acessa o array no indice
	push((int32_t)binary);													 // Empilha o valor
	atualizaPc();
}

/**
 * STORES
 */

/**
 * @brief pega inteiro e coloca no array de variaveis locais, na posicao dada por indice
 * @param void
 * @return void
 */
void istore()
{
	int32_t indice;
	int32_t valor;

	indice = frameCorrente->code[frameCorrente->pc + 1]; // pega indice
	valor = pop_op();																		 // desempilha
	frameCorrente->fields[indice] = valor;							 // poe o valor na posicao no array de var locais

	atualizaPc();
}

/**
 * @brief pega long e coloca no array de variaveis locais, na posicao dada por indice e indice + 1
 * @param void
 * @return void
 */
void lstore()
{
	int32_t indice;
	int32_t parte_alta, parte_baixa;

	indice = frameCorrente->code[frameCorrente->pc + 1]; // pega indice

	parte_baixa = pop_op(); // desempilha a parte baixa - por convencao desempilhada primeiro
	parte_alta = pop_op();	// desempilha a parte alta

	// poe parte alta e baixa no array de var locais (pela convencao a parte alta vem depois no array)
	frameCorrente->fields[indice + POS_ALTA] = parte_alta;	 // POS_ALTA = 1
	frameCorrente->fields[indice + POS_BAIXA] = parte_baixa; // POS_BAIXA = 0

	atualizaPc();
}

/**
 * @brief pega float e coloca no array de variaveis locais, na posicao dada por indice
 * @param void
 * @return void
 */
void fstore()
{
	int32_t indice;
	int32_t valor;

	indice = frameCorrente->code[frameCorrente->pc + 1]; // pega indice
	valor = pop_op();																		 // desempilha
	frameCorrente->fields[indice] = valor;							 // poe o valor na posicao no array de var locais

	atualizaPc();
}

/**
 * @brief pega double e coloca no array de variaveis locais, na posicao dada por indice e indice + 1
 * @param void
 * @return void
 */
void dstore()
{
	int32_t indice;
	int32_t parte_alta, parte_baixa;

	indice = frameCorrente->code[frameCorrente->pc + 1]; // pega indice

	parte_baixa = pop_op(); // desempilha a parte baixa - por convencao desempilhada primeiro
	parte_alta = pop_op();	// desempilha a parte alta

	// poe parte alta e baixa no array de var locais (pela convencao a parte alta vem depois no array)
	frameCorrente->fields[indice + POS_ALTA] = parte_alta;	 // POS_ALTA = 1
	frameCorrente->fields[indice + POS_BAIXA] = parte_baixa; // POS_BAIXA = 0

	atualizaPc();
}

/**
 * @brief pega referencia e coloca no array de variaveis locais, na posicao dada por indice
 * @param void
 * @return void
 */
void astore()
{
	int32_t indice;
	int32_t valor;

	indice = frameCorrente->code[frameCorrente->pc + 1]; // pega indice
	valor = pop_op();																		 // desempilha
	frameCorrente->fields[indice] = valor;							 // poe o valor na posicao no array de var locais

	atualizaPc();
}

/**
 * @brief pega inteiro e coloca na posicao 0 do array de variaveis locais
 * @param void
 * @return void
 */
void istore_0()
{
	int32_t indice;
	int32_t valor;

	indice = 0;														 // pega indice
	valor = pop_op();											 // desempilha
	frameCorrente->fields[indice] = valor; // poe o valor na posicao no array de var locais

	atualizaPc();
}

/**
 * @brief a funcao coloca um int no array de variaveis locais
 * @param void
 * @return void
 */
void istore_1()
{
	uint32_t valor;
	valor = pop_op();									// pega valor no topo da operand stack
	frameCorrente->fields[1] = valor; // coloca o valor na posicao 1 do array de variaveis locais

	atualizaPc();
}

/**
 * @brief pega inteiro e coloca na posicao 2 do array de variaveis locais
 * @param void
 * @return void
 */
void istore_2()
{
	int32_t indice;
	int32_t valor;
	indice = 2; // pega indice

	valor = pop_op();											 // desempilha
	frameCorrente->fields[indice] = valor; // poe o valor na posicao no array de var locais

	atualizaPc();
}

/**
 * @brief pega inteiro e coloca na posicao 3 do array de variaveis locais
 * @param void
 * @return void
 */
void istore_3()
{
	int32_t indice;
	int32_t valor;
	indice = 3; // pega indice

	valor = pop_op();											 // desempilha
	frameCorrente->fields[indice] = valor; // poe o valor na posicao no array de var locais

	atualizaPc();
}

/**
 * @brief pega long e coloca no array de variaveis locais, na posicao 0 e 1
 * @param void
 * @return void
 */
void lstore_0()
{

	int32_t indice;
	int32_t parte_alta, parte_baixa;

	indice = 0; // pega indice

	parte_baixa = pop_op(); // desempilha a parte baixa - por convencao desempilhada primeiro

	parte_alta = pop_op(); // desempilha a parte alta

	// poe parte alta e baixa no array de var locais (pela convencao a parte alta vem depois no array)
	frameCorrente->fields[indice + POS_ALTA] = parte_alta;	 // POS_ALTA = 1
	frameCorrente->fields[indice + POS_BAIXA] = parte_baixa; // POS_BAIXA = 0

	atualizaPc();
}

/**
 * @brief pega long e coloca no array de variaveis locais, na posicao 1 e 2
 * @param void
 * @return void
 */
void lstore_1()
{
	int32_t indice;
	int32_t parte_alta, parte_baixa;
	indice = 1; // pega indice

	parte_baixa = pop_op(); // desempilha a parte baixa - por convencao desempilhada primeiro
	parte_alta = pop_op();	// desempilha a parte alta

	// poe parte alta e baixa no array de var locais (pela convencao a parte alta vem depois no array)
	frameCorrente->fields[indice + POS_ALTA] = parte_alta;	 // POS_ALTA = 1
	frameCorrente->fields[indice + POS_BAIXA] = parte_baixa; // POS_BAIXA = 0

	atualizaPc();
}

/**
 * @brief pega long e coloca no array de variaveis locais, na posicao 2 e 3
 * @param void
 * @return void
 */
void lstore_2()
{
	int32_t indice;
	int32_t parte_alta, parte_baixa;
	indice = 2; // pega indice

	parte_baixa = pop_op(); // desempilha a parte baixa - por convencao desempilhada primeiro
	parte_alta = pop_op();	// desempilha a parte alta

	// poe parte alta e baixa no array de var locais (pela convencao a parte alta vem depois no array)
	frameCorrente->fields[indice + POS_ALTA] = parte_alta;	 // POS_ALTA = 1
	frameCorrente->fields[indice + POS_BAIXA] = parte_baixa; // POS_BAIXA = 0

	atualizaPc();
}

/**
 * @brief pega long e coloca no array de variaveis locais, na posicao 3 e 4
 * @param void
 * @return void
 */
void lstore_3()
{
	int32_t indice;
	int32_t parte_alta, parte_baixa;
	indice = 3; // pega indice

	parte_baixa = pop_op(); // desempilha a parte baixa - por convencao desempilhada primeiro
	parte_alta = pop_op();	// desempilha a parte alta

	// poe parte alta e baixa no array de var locais (pela convencao a parte alta vem depois no array)
	frameCorrente->fields[indice + POS_ALTA] = parte_alta;	 // POS_ALTA = 1
	frameCorrente->fields[indice + POS_BAIXA] = parte_baixa; // POS_BAIXA = 0

	atualizaPc();
}

/**
 * @brief pega float e coloca no array de variaveis locais na posicao 0
 * @param void
 * @return void
 */
void fstore_0()
{
	int32_t indice;
	int32_t valor;
	indice = 0; // pega indice

	valor = pop_op();											 // desempilha
	frameCorrente->fields[indice] = valor; // poe o valor na posicao no array de var locais

	atualizaPc(); // incrementa pc
}

/**
 * @brief pega float e coloca no array de variaveis locais na posicao 1
 * @param void
 * @return void
 */
void fstore_1()
{
	int32_t indice;
	int32_t valor;
	indice = 1; // pega indice

	valor = pop_op();											 // desempilha
	frameCorrente->fields[indice] = valor; // poe o valor na posicao no array de var locais

	atualizaPc(); // incrementa pc
}

/**
 * @brief pega float e coloca no array de variaveis locais na posicao 2
 * @param void
 * @return void
 */
void fstore_2()
{
	int32_t indice;
	int32_t valor;
	indice = 2; // pega indice

	valor = pop_op();											 // desempilha
	frameCorrente->fields[indice] = valor; // poe o valor na posicao no array de var locais

	atualizaPc(); // incrementa pc
}

/**
 * @brief pega float e coloca no array de variaveis locais na posicao 3
 * @param void
 * @return void
 */
void fstore_3()
{
	int32_t indice;
	int32_t valor;
	indice = 3; // pega indice

	valor = pop_op();											 // desempilha
	frameCorrente->fields[indice] = valor; // poe o valor na posicao no array de var locais

	atualizaPc(); // incrementa pc
}

/**
 * @brief pega double e coloca no array de variaveis locais, na posicao iniciada em 0
 * @param void
 * @return void
 */
void dstore_0()
{
	int32_t indice;
	int32_t parte_alta, parte_baixa;
	indice = 0; // pega indice

	parte_baixa = pop_op(); // desempilha a parte baixa - por convencao desempilhada primeiro
	parte_alta = pop_op();	// desempilha a parte alta

	// poe parte alta e baixa no array de var locais (pela convencao a parte alta vem depois no array)
	frameCorrente->fields[indice + POS_ALTA] = parte_alta;	 // POS_ALTA = 1
	frameCorrente->fields[indice + POS_BAIXA] = parte_baixa; // POS_BAIXA = 0

	atualizaPc(); // incrementa pc
}

/**
 * @brief pega double e coloca no array de variaveis locais, na posicao iniciada em 1
 * @param void
 * @return void
 */
void dstore_1()
{
	int32_t indice;
	int32_t parte_alta, parte_baixa;
	indice = 1; // pega indice

	parte_baixa = pop_op(); // desempilha a parte baixa - por convencao desempilhada primeiro
	parte_alta = pop_op();	// desempilha a parte alta

	// poe parte alta e baixa no array de var locais (pela convencao a parte alta vem depois no array)
	frameCorrente->fields[indice + POS_ALTA] = parte_alta;	 // POS_ALTA = 1
	frameCorrente->fields[indice + POS_BAIXA] = parte_baixa; // POS_BAIXA = 0

	atualizaPc(); // incrementa pc
}

/**
 * @brief pega double e coloca no array de variaveis locais, na posicao iniciada em 2
 * @param void
 * @return void
 */
void dstore_2()
{
	int32_t indice;
	int32_t parte_alta, parte_baixa;
	indice = 2; // pega indice

	parte_baixa = pop_op(); // desempilha a parte baixa - por convencao desempilhada primeiro
	parte_alta = pop_op();	// desempilha a parte alta

	// poe parte alta e baixa no array de var locais (pela convencao a parte alta vem depois no array)
	frameCorrente->fields[indice + POS_ALTA] = parte_alta;	 // POS_ALTA = 1
	frameCorrente->fields[indice + POS_BAIXA] = parte_baixa; // POS_BAIXA = 0

	atualizaPc(); // incrementa pc
}

/**
 * @brief pega double e coloca no array de variaveis locais, na posicao iniciada em 3
 * @param void
 * @return void
 */
void dstore_3()
{
	int32_t indice;
	int32_t parte_alta, parte_baixa;
	indice = 3; // pega indice

	parte_baixa = pop_op(); // desempilha a parte baixa - por convencao desempilhada primeiro
	parte_alta = pop_op();	// desempilha a parte alta

	// poe parte alta e baixa no array de var locais (pela convencao a parte alta vem depois no array)
	frameCorrente->fields[indice + POS_ALTA] = parte_alta;	 // POS_ALTA = 1
	frameCorrente->fields[indice + POS_BAIXA] = parte_baixa; // POS_BAIXA = 0

	atualizaPc(); // incrementa pc
}

/**
 * @brief pega referencia e coloca no array de variaveis locais, na posicao 0
 * @param void
 * @return void
 */
void astore_0()
{
	int32_t indice;
	int32_t valor;
	indice = 0; // pega indice

	valor = pop_op();											 // desempilha
	frameCorrente->fields[indice] = valor; // poe o valor na posicao no array de var locais

	atualizaPc();
}

/**
 * @brief pega referencia e coloca no array de variaveis locais, na posicao dada por 1
 * @param void
 * @return void
 */
void astore_1()
{
	int32_t indice;
	int32_t valor;
	indice = 1; // pega indice

	valor = pop_op();											 // desempilha
	frameCorrente->fields[indice] = valor; // poe o valor na posicao no array de var locais

	atualizaPc(); // incrementa pc
}

/**
 * @brief pega referencia e coloca no array de variaveis locais, na posicao dada por 2
 * @param void
 * @return void
 */
void astore_2()
{
	int32_t indice;
	int32_t valor;
	indice = 2; // pega indice

	valor = pop_op();											 // desempilha
	frameCorrente->fields[indice] = valor; // poe o valor na posicao no array de var locais

	atualizaPc(); // incrementa pc
}

/**
 * @brief pega referencia e coloca no array de variaveis locais, na posicao dada por 3
 * @param void
 * @return void
 */
void astore_3()
{
	int32_t indice;
	int32_t valor;
	indice = 3; // pega indice

	valor = pop_op();											 // desempilha
	frameCorrente->fields[indice] = valor; // poe o valor na posicao no array de var locais

	atualizaPc(); // incrementa pc
}

/**
 * @brief Obtem da pilha o valor a ser atribuido, o indice a ser acessado
 * e obtem uma referencia ao vetor previamente alocado
 * Acessa o vetor no indice obtido e atribui o valor
 * @param void
 * @return void
 */
void iastore()
{

	int32_t *ref; // Referencia pro array
	int32_t indice, valor;

	valor = pop_op();	 // Pega o valor a ser atribuido da pilha de operandos
	indice = pop_op(); // Pega o indice do vetor a ser acessado

	ref = (int32_t *)pop_op(); // Pega referencia do array a ser acessado
	ref[indice] = valor;			 // Acessa o array no indice e atribui com o valor obtido da pilha

	atualizaPc();
}

/**
 * @brief Obtem da pilha o valor a ser atribuido, o indice a ser acessado
 * e obtem uma referencia ao vetor previamente alocado
 * Acessa o vetor no indice obtido e atribui o valor
 * @param void
 * @return void
 */
void lastore()
{
	static int16_t countPos = 0;
	int32_t alta, baixa;

	alta = pop_op();	// Obtem parte alta
	baixa = pop_op(); // Obtem parte baixa

	int32_t indice = pop_op(); // Obtem indice de acesso ao array

	int32_t *referencia;
	referencia = (int32_t *)pop_op(); // Referencia pro array.

	referencia[countPos + indice] = baixa;
	referencia[countPos + indice + 1] = alta;
	countPos += 2;
	atualizaPc();
}

/**
 * @brief Obtem da pilha o valor a ser atribuido, o indice a ser acessado
 * e obtem uma referencia ao vetor previamente alocado
 * Acessa o vetor no indice obtido e atribui o valor
 * @param void
 * @return void
 */
void fastore()
{
	char *tipo = "F";
	tipoGlobal = tipo;
	int32_t *ref; // Referencia pro array
	int32_t indice, valor;

	valor = pop_op();					 // Pega o valor a ser atribuido da pilha de operandos
	indice = pop_op();				 // Pega o indice do vetor a ser acessado
	ref = (int32_t *)pop_op(); // Pega referencia do array a ser acessado
	ref[indice] = valor;			 // Acessa o array no indice e atribui com o valor obtido da pilha

	atualizaPc();
}

/**
 * @brief Obtem da pilha o valor a ser atribuido, o indice a ser acessado
 * e obtem uma referencia ao vetor previamente alocado
 * Acessa o vetor no indice obtido e atribui o valor
 * @param void
 * @return void
 */
void dastore()
{
	static int16_t countPos = 0;
	int32_t alta, baixa;

	alta = pop_op();	// Obtem parte alta
	baixa = pop_op(); // Obtem parte baixa

	int32_t indice = pop_op(); // Obtem indice de acesso ao array

	int32_t *referencia; // Referencia pro array.
	referencia = (int32_t *)pop_op();

	referencia[countPos + indice] = baixa;
	referencia[countPos + indice + 1] = alta;
	countPos += 2;
	atualizaPc();
}

/**
 * @brief Obtem da pilha o valor a ser atribuido, o indice a ser acessado
 * e obtem uma referencia ao vetor previamente alocado
 * Acessa o vetor no indice obtido e atribui o valor
 * @param void
 * @return void
 */
void aastore()
{

	int32_t *ref; // Referencia pro array
	int32_t indice, valor;

	valor = pop_op();	 // Pega o valor a ser atribuido da pilha de operandos
	indice = pop_op(); // Pega o indice do vetor a ser acessado

	ref = (int32_t *)pop_op(); // Pega referencia do array a ser acessado
	ref[indice] = valor;			 // Acessa o array no indice e atribui com o valor obtido da pilha

	atualizaPc();
}

/**
 * @brief Obtem da pilha o valor a ser atribuido, o indice a ser acessado
 * e obtem uma referencia ao vetor previamente alocado
 * Acessa o vetor no indice obtido e atribui o valor
 * @param void
 * @return void
 */
void bastore()
{

	int32_t *ref; // Referencia pro array
	int32_t indice, valor;

	valor = pop_op();	 // Pega o valor a ser atribuido da pilha de operandos
	indice = pop_op(); // Pega o indice do vetor a ser acessado

	ref = (int32_t *)pop_op();	 // Pega referencia do array a ser acessado
	ref[indice] = (int8_t)valor; // Acessa o array no indice e atribui com o valor obtido da pilha

	atualizaPc();
}

/**
 * @brief Obtem da pilha o valor a ser atribuido, o indice a ser acessado
 * e obtem uma referencia ao vetor previamente alocado
 * Acessa o vetor no indice obtido e atribui o valor
 * @param void
 * @return void
 */
void castore()
{

	int32_t *ref; // Referencia pro array
	int32_t indice, valor;

	valor = pop_op();	 // Pega o valor a ser atribuido da pilha de operandos
	indice = pop_op(); // Pega o indice do vetor a ser acessado

	ref = (int32_t *)pop_op();		// Pega referencia do array a ser acessado
	ref[indice] = (int16_t)valor; // Acessa o array no indice e atribui com o valor obtido da pilha

	atualizaPc();
}

/**
 * @brief Obtem da pilha o valor a ser atribuido, o indice a ser acessado
 * e obtem uma referencia ao vetor previamente alocado
 * Acessa o vetor no indice obtido e atribui o valor
 * @param void
 * @return void
 */
void sastore()
{

	int32_t *ref; // Referencia pro array
	int32_t indice, valor;

	valor = pop_op();	 // Pega o valor a ser atribuido da pilha de operandos
	indice = pop_op(); // Pega o indice do vetor a ser acessado

	ref = (int32_t *)pop_op();		// Pega referencia do array a ser acessado
	ref[indice] = (int16_t)valor; // Acessa o array no indice e atribui com o valor obtido da pilha

	atualizaPc();
}

/**
 * @brief Funcao que desempilha um valor da pilha de operandos
 * @param void
 * @return void
 */
void pop()
{
	pop_op();
	atualizaPc();
}

/**
 * @brief Funcao que desempilha dois valores da pilha de operandos
 * @param void
 * @return void
 */
void pop2()
{
	// Desempilha dois valores
	pop_op();
	pop_op();
	atualizaPc();
}

/**
 * @brief Instrucao que retira valor da pilha e adiciona de volta duplicado
 * @param void
 * @return void
 */
void dup()
{
	int32_t retPilha;
	retPilha = pop_op(); // Desempilha

	// Duplica
	push(retPilha);
	push(retPilha);
	atualizaPc();
}

/**
 * @brief Instrucao que duplica valor da pilha e adiciona de volta de forma que se repita de forma nao ordenada
 * @param void
 * @return void
 */
void dup_x1()
{
	int32_t aux1, aux2;

	// Desempilha
	aux1 = pop_op();
	aux2 = pop_op();

	// Duplica
	push(aux1);
	push(aux2);

	push(aux1); // Adiciona de volta

	atualizaPc();
}

/**
 * @brief Instrucao que duplica valor da pilha e adiciona dois ou tres valores de volta
 * @param void
 * @return void
 */
void dup_x2()
{
	// TODO : fazer para a forma 2
	int32_t aux1, aux2, aux3;

	// Desempilha
	aux1 = pop_op();
	aux2 = pop_op();
	aux3 = pop_op();

	// Duplica
	push(aux1);
	push(aux3);
	push(aux2);
	push(aux1);

	atualizaPc();
}

/**
 * @brief Instrucao que duplica valor da pilha e adiciona dois valores de volta
 * @param void
 * @return void
 */
void dup2()
{
	// TODO : fazer para a forma 2
	int32_t aux1, aux2, aux3;

	// Desempilha
	aux1 = pop_op();
	aux2 = pop_op();

	// Duplica
	push(aux2);
	push(aux1);
	push(aux2);
	push(aux1);

	atualizaPc();
}

/**
 * @brief Instrucao que duplica valor da pilha e adiciona dois ou tres valores de volta
 * @param void
 * @return void
 */
void dup2_x1()
{
	// TODO : fazer para a forma 2
	int32_t aux1, aux2, aux3;

	// Desempilha
	aux1 = pop_op();
	aux2 = pop_op();
	aux3 = pop_op();

	// Duplica
	push(aux2);
	push(aux1);
	push(aux3);
	push(aux2);
	push(aux1);

	atualizaPc();
}

/**
 * @brief Instrucao que duplica valor o primeiro ou segundo valor da pilha e
 * adiciona dois ou tres ou quatro valores de volta
 * @param void
 * @return void
 */
void dup2_x2()
{
	// TODO : fazer para a forma 2
	int32_t aux1, aux2, aux3, aux4;

	// Desempilha
	aux1 = pop_op();
	aux2 = pop_op();
	aux3 = pop_op();
	aux4 = pop_op();

	// Duplica
	push(aux2);
	push(aux1);
	push(aux4);
	push(aux3);
	push(aux2);
	push(aux1);

	atualizaPc();
}

/**
 * @brief Desempilha dois valores da pilha e troca de posicao um com o outro
 * @param void
 * @return void
 */
void swap()
{
	int32_t val1, val2;

	// Desempilha os dois valores
	val1 = pop_op();
	val2 = pop_op();

	// Troca sua posicões
	push(val1);
	push(val2);

	atualizaPc();
}

/**
 * @brief Funcao desempilha dois valores inteiros, soma-os e empilha resultado
 * @param void
 * @return void
 */
void iadd()
{
	int32_t v1, v2;
	v2 = pop_op();
	v1 = pop_op();

	push(v1 + v2);

	atualizaPc();
}

/**
 * @brief Funcao desempilha dois valores long, soma-os e empilha resultado
 * @param void
 * @return void
 */
void ladd()
{
	int32_t baixa, alta;

	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(long)

	int64_t lVal = alta; // Atribui parte alta primeiro
	lVal <<= 32;				 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	lVal = lVal + baixa; // Preenche os 32 bits inferiores com a parte baixa (somar pois os 32 bits da parte baixa estao zerados)

	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(long)

	int64_t lVal1 = alta;	 // Atribui parte alta primeiro
	lVal1 <<= 32;					 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	lVal1 = lVal1 + baixa; // Preenche os 32 bits inferiores com a parte baixa (somar pois os 32 bits da parte baixa estao zerados)

	int64_t resultado = lVal1 + lVal; // Soma os dois valores

	// Converte para parte alta e baixa novamente para empilhar
	alta = resultado >> 32;
	baixa = resultado & 0xffffffff;

	// empilha o resultado
	push(alta);
	push(baixa);

	atualizaPc();
}

/**
 * @brief Funcao desempilha dois valores float, soma-os e empilha resultado
 * @param void
 * @return void
 */
void fadd()
{
	float fVal1, fVal2;

	// Desempilha os dois valores
	int32_t aux1 = pop_op();
	int32_t aux2 = pop_op();

	// Converte para float e nao perde precisao
	memcpy(&fVal1, &aux1, sizeof(int32_t));
	memcpy(&fVal2, &aux2, sizeof(int32_t));

	float resultado = fVal1 + fVal2; // Soma os dois valores em float

	int32_t retPilha;
	memcpy(&retPilha, &resultado, sizeof(int32_t)); // copia para um int32_t

	push(retPilha); // Empilha

	atualizaPc();
}

/**
 * @brief Desempilha dois valores, soma e empilha dois valores double
 * @param void
 * @return void
 */
void dadd()
{
	// Parte alta e baixa do double
	int32_t alta;
	int32_t baixa;

	// Obtem parte baixa primeiro - Foi empilhada por ultimo (topo)
	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(double)

	int64_t dVal = alta; // Atribui parte alta primeiro
	dVal <<= 32;				 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	dVal = dVal + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	double valorDouble1; // Copia os bytes do int64_t para um double (memcpy copia 64 bits de dVal para valorDouble1)
	memcpy(&valorDouble1, &dVal, sizeof(int64_t));

	// Obtem parte baixa primeiro - Foi empilhada por ultimo (topo)
	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(double)

	dVal = alta;				 // Atribui parte alta primeiro
	dVal <<= 32;				 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	dVal = dVal + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	double valorDouble2; // Copia os bytes do int64_t para um double (memcpy copia 64 bits de dVal para valorDouble2)
	memcpy(&valorDouble2, &dVal, sizeof(int64_t));

	double doubleSomado = valorDouble1 + valorDouble2; // Soma os dois valores double

	int64_t valorPilha; // Necessario converter mais uma vez o double somado para int64 para empilhar corretamente
	memcpy(&valorPilha, &doubleSomado, sizeof(int64_t));

	// Converte para parte alta e baixa novamente para empilhar
	alta = valorPilha >> 32;
	baixa = valorPilha & 0xffffffff;

	// Empilha
	push(alta);
	push(baixa);

	atualizaPc();
}

/**
 * @brief Funcao desempilha dois valores inteiros, subtrai e empilha resultado
 * @param void
 * @return void
 */
void isub()
{
	int32_t v1, v2;
	v2 = pop_op();
	v1 = pop_op();
	push(v1 - v2);

	atualizaPc();
}

/**
 * @brief Funcao desempilha dois valores long, subtrai e empilha resultado
 * @param void
 * @return void
 */
void lsub()
{
	int32_t baixa, alta;

	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(long)

	int64_t lVal = alta; // Atribui parte alta primeiro
	lVal <<= 32;				 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	lVal = lVal + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(long)

	int64_t lVal1 = alta;	 // Atribui parte alta primeiro
	lVal1 <<= 32;					 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	lVal1 = lVal1 + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	int64_t resultado = lVal1 - lVal; // subtrai os dois valores

	// Converte para parte alta e baixa novamente para empilhar
	alta = resultado >> 32;
	baixa = resultado & 0xffffffff;

	// Empilha
	push(alta);
	push(baixa);

	atualizaPc();
}

/**
 * @brief Funcao desempilha dois valores float, subtrai e empilha resultado
 * @param void
 * @return void
 */
void fsub()
{
	float fVal1, fVal2;

	// Desempilha os dois valores
	int32_t aux2 = pop_op();
	int32_t aux1 = pop_op();

	// Converte para float e nao perde precisao
	memcpy(&fVal1, &aux1, sizeof(int32_t));
	memcpy(&fVal2, &aux2, sizeof(int32_t));

	float resultado = fVal1 - fVal2; // Subtrai os dois valores em float

	int32_t retPilha;
	memcpy(&retPilha, &resultado, sizeof(int32_t)); // copia para um int32_t

	push(retPilha); // Empilha

	atualizaPc();
}

/**
 * @brief Desempilha 2 valores double da pilha, subtrai e empilha o resultado
 * @param void
 * @return void
 */
void dsub()
{
	// Parte alta e baixa do double
	int32_t alta;
	int32_t baixa;

	// Obtem parte baixa primeiro - Foi empilhada por ultimo (topo)
	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(double)

	int64_t dVal = alta; // Atribui parte alta primeiro
	dVal <<= 32;				 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	dVal = dVal + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	double valorDouble1; // Copia os bytes do int64_t para um double (memcpy copia 64 bits de dVal para valorDouble1)
	memcpy(&valorDouble1, &dVal, sizeof(int64_t));

	// Obtem parte baixa primeiro -> Foi empilhada por ultimo(topo)
	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(double)

	dVal = alta;				 // Atribui parte alta primeiro
	dVal <<= 32;				 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	dVal = dVal + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	double valorDouble2; // Copia os bytes do int64_t para um double (memcpy copia 64 bits de dVal para valorDouble2)
	memcpy(&valorDouble2, &dVal, sizeof(int64_t));

	double doubleSubtraido = valorDouble2 - valorDouble1; // Soma os dois valores double

	int64_t valorPilha; // Converte mais uma vez o double somado para int64 para empilhar corretamente
	memcpy(&valorPilha, &doubleSubtraido, sizeof(int64_t));

	// Converte para parte alta e baixa novamente para empilhar
	alta = valorPilha >> 32;
	baixa = valorPilha & 0xffffffff;

	// Empilha
	push(alta);
	push(baixa);

	atualizaPc();
}

/**
 * @brief Desempilha 2 valores da pilha, multiplica-os e empilha o resultado
 * @param void
 * @return void
 */
void imul()
{
	int32_t v1 = pop_op();
	int32_t v2 = pop_op();
	push((int32_t)(v1 * v2));
	atualizaPc();
}

/**
 * Desempilha 2 valores da pilha, multiplica-os e empilha o resultado
 * @param void
 * @return void
 */
void lmul()
{

	int32_t baixa, alta;

	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(long)

	int64_t lVal = alta; // Atribui parte alta primeiro
	lVal <<= 32;				 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	lVal = lVal + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(long)

	int64_t lVal1 = alta;	 // Atribui parte alta primeiro
	lVal1 <<= 32;					 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	lVal1 = lVal1 + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	int64_t resultado = lVal1 * lVal; // multiplica os dois valores

	// Converte para parte alta e baixa novamente para empilhar
	alta = resultado >> 32;
	baixa = resultado & 0xffffffff;

	// Empilha
	push(alta);
	push(baixa);

	atualizaPc();
}

/**
 * @brief Desempilha 2 valores da pilha, multiplica-os e empilha o resultado
 * @param void
 * @return void
 */
void fmul()
{
	float fVal1, fVal2;

	// Desempilha os dois valores
	int32_t aux1 = pop_op();
	int32_t aux2 = pop_op();

	// Converte para float e nao perde precisao
	memcpy(&fVal1, &aux1, sizeof(int32_t));
	memcpy(&fVal2, &aux2, sizeof(int32_t));

	float resultado = fVal1 * fVal2; // multiplica os dois valores em float

	int32_t retPilha; // copia para um int32_t
	memcpy(&retPilha, &resultado, sizeof(int32_t));

	// Empilha
	push(retPilha);

	atualizaPc();
}

/**
 * @brief Desempilha 2 valores double da pilha, multiplica-os e empilha o resultado
 * @param void
 * @return void
 */
void dmul()
{
	// Parte alta e baixa do double
	int32_t alta;
	int32_t baixa;

	// Obtem parte baixa primeiro -> Foi empilhada por ultimo(topo)
	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(double)

	int64_t dVal = alta; // Atribui parte alta primeiro
	dVal <<= 32;				 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	dVal = dVal + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	double valorDouble1; // Copia os bytes do int64_t para um double (memcpy copia 64 bits de dVal para valorDouble1)
	memcpy(&valorDouble1, &dVal, sizeof(int64_t));

	// Obtem parte baixa primeiro -> Foi empilhada por ultimo(topo)
	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(double)

	dVal = alta;				 // Atribui parte alta primeiro
	dVal <<= 32;				 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	dVal = dVal + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	double valorDouble2; // Copia os bytes do int64_t para um double (memcpy copia 64 bits de dVal para valorDouble2)
	memcpy(&valorDouble2, &dVal, sizeof(int64_t));

	double doubleMultiplicado = valorDouble1 * valorDouble2; // Soma os dois valores double

	int64_t valorPilha; // Converte mais uma vez o double somado para int64 para empilhar corretamente
	memcpy(&valorPilha, &doubleMultiplicado, sizeof(int64_t));

	// Converte para parte alta e baixa novamente para empilhar
	alta = valorPilha >> 32;
	baixa = valorPilha & 0xffffffff;

	// Empilha
	push(alta);
	push(baixa);

	atualizaPc();
}

/**
 * @brief Desempilha 2 valores inteiros da pilha, divide-os e empilha o resultado
 * @param void
 * @return void
 */
void idiv()
{
	// v2 vem primeiro na pilha de op
	int32_t v2 = pop_op();
	int32_t v1 = pop_op();
	push((int32_t)(v1 / v2));
	atualizaPc();
}

/**
 * @brief Desempilha 2 valores long da pilha, divide-os e empilha o resultado
 * @param void
 * @return void
 */
void ins_ldiv()
{
	int32_t baixa, alta;

	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(long)

	int64_t lVal = alta; // Atribui parte alta primeiro
	lVal <<= 32;				 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	lVal = lVal + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(long)

	int64_t lVal1 = alta;	 // Atribui parte alta primeiro
	lVal1 <<= 32;					 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	lVal1 = lVal1 + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	int64_t resultado = lVal1 / lVal; // Divide os dois valores

	// Converte para parte alta e baixa novamente para empilhar
	alta = resultado >> 32;
	baixa = resultado & 0xffffffff;

	// Empilha
	push(alta);
	push(baixa);

	atualizaPc();
}

/**
 * @brief Desempilha 2 valores float da pilha, divide-os e empilha o resultado
 * @param void
 * @return void
 */
void fdiv()
{
	float fVal1, fVal2;

	// Desempilha os dois valores
	int32_t aux2 = pop_op();
	int32_t aux1 = pop_op();

	// Converte para float e nao perde precisao
	memcpy(&fVal1, &aux1, sizeof(int32_t));
	memcpy(&fVal2, &aux2, sizeof(int32_t));

	// Divide os dois valores em float
	float resultado = fVal1 / fVal2;

	int32_t retPilha; // copia para um int32_t
	memcpy(&retPilha, &resultado, sizeof(int32_t));

	push(retPilha); // Empilha

	atualizaPc();
}

/**
 * @brief Desempilha dois valores double da pilha divide e empilha o resultado
 * @param void
 * @return void
 */
void ddiv()
{
	int32_t alta, baixa, alta1, baixa1;

	// Partes altas e baixas dos dois doubles.
	baixa1 = pop_op();
	alta1 = pop_op();

	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(double)

	int64_t dVal = alta1; // Atribui parte alta primeiro
	dVal <<= 32;					// Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	dVal = dVal + baixa1; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	double v1; // Copia os bytes do int64_t para um double (memcpy copia 64 bits de dVal para valorDouble1)
	memcpy(&v1, &dVal, sizeof(double));

	// Converter os numeros 32 bits para 64 bits(double)

	dVal = alta;				 // Atribui parte alta primeiro
	dVal <<= 32;				 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	dVal = dVal + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	// Finalmente copio os bytes do int64_t para um double
	// memcpy copia 64 bits de dVal para valorDouble1
	double v2;
	memcpy(&v2, &dVal, sizeof(double));

	double resultado = v2 / v1;

	int64_t pilhaVal; // Converte mais uma vez o double somado para int64 para empilhar corretamente
	memcpy(&pilhaVal, &resultado, sizeof(int64_t));

	// Converte para parte alta e baixa novamente para empilhar
	alta = pilhaVal >> 32;
	baixa = pilhaVal & 0xffffffff;

	// Empilha
	push(alta);
	push(baixa);

	atualizaPc();
}

/**
 * @brief Desempilha 2 valores inteiros da pilha, obtem o resto da divisao e empilha o resultado
 * @param void
 * @return void
 */
void irem()
{
	// operando v2 esta primeiro na pilha
	int32_t v2 = pop_op();
	int32_t v1 = pop_op();

	push((int32_t)(v1 % v2));

	atualizaPc();
}

/**
 * @brief Desempilha 2 valores long da pilha, obtem o resto da divisao e empilha o resultado
 * @param void
 * @return void
 */
void lrem()
{
	int32_t baixa, alta;

	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(long)

	int64_t lVal = alta; // Atribui parte alta primeiro
	lVal <<= 32;				 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	lVal = lVal + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(long)

	int64_t lVal1 = alta;	 // Atribui parte alta primeiro
	lVal1 <<= 32;					 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	lVal1 = lVal1 + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	int64_t resultado = lVal1 % lVal; // multiplica os dois valores

	// Converte para parte alta e baixa novamente para empilhar
	alta = resultado >> 32;
	baixa = resultado & 0xffffffff;

	// Empilha
	push(alta);
	push(baixa);

	atualizaPc();
}

/**
 * @brief Desempilha 2 valores float da pilha, obtem o resto da divisao e empilha o resultado
 * @param void
 * @return void
 */
void frem()
{
	float fVal1, fVal2;

	// Desempilha os dois valores - aux 2 sai primeiro da pilha de operandos
	int32_t aux2 = pop_op();
	int32_t aux1 = pop_op();

	// Converte para float e nao perde precisao
	memcpy(&fVal1, &aux1, sizeof(int32_t));
	memcpy(&fVal2, &aux2, sizeof(int32_t));

	float resultado = fmodf(fVal1, fVal2); // Utiliza funcao da math.h para obter o modulo de floats os dois valores em float

	int32_t retPilha; // copia para um int32_t
	memcpy(&retPilha, &resultado, sizeof(int32_t));

	push(retPilha); // Empilha

	atualizaPc();
}

/**
 * @brief Desempilha 2 valores double da pilha, obtem o resto da divisao e empilha o resultado
 * @param void
 * @return void
 */
void _drem()
{
	// Partes altas e baixas dos dois doubles
	int32_t alta, baixa, alta1, baixa1;

	baixa1 = pop_op();
	alta1 = pop_op();

	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(double)

	int64_t dVal = alta1; // Atribui parte alta primeiro
	dVal <<= 32;					// Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	dVal = dVal + baixa1; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	double v1; // Copia os bytes do int64_t para um double (memcpy copia 64 bits de dVal para v1)
	memcpy(&v1, &dVal, sizeof(double));

	// Converter os numeros 32 bits para 64 bits(double)

	dVal = alta;				 // Atribui parte alta primeiro
	dVal <<= 32;				 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	dVal = dVal + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	double v2; // Copia os bytes do int64_t para um double (memcpy copia 64 bits de dVal para v2)
	memcpy(&v2, &dVal, sizeof(double));

	double resultado = fmod(v2, v1);

	int64_t pilhaVal; // Converte mais uma vez o double somado para int64 para empilhar corretamente
	memcpy(&pilhaVal, &resultado, sizeof(int64_t));

	// Converte para parte alta e baixa novamente para empilhar
	alta = pilhaVal >> 32;
	baixa = pilhaVal & 0xffffffff;

	// Empilha
	push(alta);
	push(baixa);

	atualizaPc();
}

/**
 * @brief Desempilha um int ,negativa e empilha o resultado
 * @param void
 * @return void
 */
void ineg()
{
	int32_t retPilha = pop_op(); // Desempilha valor da pilha
	int32_t aux = -retPilha;		 // Negativa
	push(aux);									 // Empilha valor negativado
	atualizaPc();
}

/**
 * @brief Desempilha um long (do java -> no c long tem 32bits), negativa e empilha o resultado
 * @param void
 * @return void
 */
void lneg()
{
	int32_t baixa, alta;

	// Desempilha parte alta e baixa de um long da pilha
	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(long)

	int64_t lVal = alta; // Atribui parte alta primeiro
	lVal <<= 32;				 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	lVal = lVal | baixa; // Preenche os 32 bits inferiores com a parte baixa

	lVal = -lVal; // Negativa o valor

	// Converte para parte alta e baixa novamente para empilhar
	alta = lVal >> 32;
	baixa = lVal & 0xffffffff;

	// Empilha
	push(alta);
	push(baixa);

	atualizaPc();
	foi_lneg = true;
}

/**
 * @brief Desempilha um float ,negativa e empilha o resultado
 * @param void
 * @return void
 */
void fneg()
{
	float fVal;

	int32_t retPilha = pop_op();							 // Obtem valor da pilha em int32_t
	memcpy(&fVal, &retPilha, sizeof(float));	 // Copia bits para um float para nao perder precisao -> Alternativa UNION
	fVal = -fVal;															 // Negativa o valor
	memcpy(&retPilha, &fVal, sizeof(int32_t)); // Copia  bits para um int32_t para empilhar corretamente e n perder precisao
	push(retPilha);														 // Empilha valor de ponto flutuante em int32_t

	atualizaPc();
}

/**
 * @brief Desempilha um double ,negativa e empilha o resultado
 * @param void
 * @return void
 */
void dneg()
{

	int32_t baixa, alta;

	// Desempilha parte alta e baixa do valor double
	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(double)

	int64_t dVal = alta; // Atribui parte alta primeiro
	dVal <<= 32;				 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	dVal = dVal + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	double valorDouble1; // Copia os bytes do int64_t para um double (memcpy copia 64 bits de dVal para valorDouble1)
	memcpy(&valorDouble1, &dVal, sizeof(int64_t));

	valorDouble1 = -valorDouble1; // Negativa o valor double

	memcpy(&dVal, &valorDouble1, sizeof(int64_t)); // Copia os bytes para um int64_t para nao perder precisao

	// Converte para parte alta e baixa novamente para empilhar
	alta = dVal >> 32;
	baixa = dVal & 0xffffffff;

	// Empilha
	push(alta);
	push(baixa);

	atualizaPc();
}

/**
 * @brief Desempilha quantidade a ser shiftada. Desempilha valor inteiro a ser shiftado
 * shifta-o a esquerda e empilha o resultado
 * OBS: shifta no maximo 32 bits - Com sinal
 * @param void
 * @return void
 */
void ishl()
{
	int32_t shift = pop_op(); // Pega quantidade a ser shiftada
	shift = shift & 0x1f;			// limita em 32 bits (0x1f)

	int32_t sVal = pop_op(); // Obtem valor da pilha
	sVal = sVal << shift;		 // shifta a esquerda
	push(sVal);							 // Empilha o resultado

	atualizaPc();
}

/**
 * @brief Desempilha quantidade a ser shiftada. Desempilha valor long a ser shiftado
 * shifta-o a esquerda e empilha o resultado
 * OBS: shifta no maximo 64 bits. Com sinal
 * @param void
 * @return void
 */
void lshl()
{

	int32_t shift = pop_op(); // Pega quantidade a ser shiftada
	shift = shift & 0x3f;			// limita em 64 bits (0x1f)

	int32_t baixa, alta;
	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(long)

	int64_t lVal = alta; // Atribui parte alta primeiro
	lVal <<= 32;				 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	lVal = lVal + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	lVal = lVal << shift; // Shift

	// Converte para parte alta e baixa novamente para empilhar
	alta = lVal >> 32;
	baixa = lVal & 0xffffffff;

	// Empilha
	push(alta);
	push(baixa);

	atualizaPc();
}

/**
 * @brief Desempilha quantidade a ser shiftada. Desempilha valor inteiro a ser shiftado
 * shifta-o a direita e empilha o resultado
 * OBS: shifta no maximo 32 bits. Com sinal -> e equivalente a dividir o valor por 2
 * @param void
 * @return void
 */
void ishr()
{
	// Pega quantidade a ser shiftada e limita em 32 bits (0x1f)
	int32_t shift = pop_op();
	shift = shift & 0x1f;

	int32_t sVal = pop_op(); // Obtem valor da pilha

	int32_t i = 0;
	while (i < shift) // shifta a direita(divide n vezes por 2)
	{
		sVal = sVal / 2;
		i += 1;
	}

	push(sVal); // Empilha

	atualizaPc();
}

/**
 * @brief Funcao que faz um shift aritmetico de long
 * @param void
 * @return void
 */
void lshr()
{
	int32_t v2 = pop_op(); // pega value 2

	// pega value 1 - correspondente ao long
	int32_t baixa, alta;
	baixa = pop_op();
	alta = pop_op();
	int64_t lVal = alta;
	lVal <<= 32;
	lVal = lVal + baixa;

	lVal = lVal << v2; // faz o shift

	// coloca result de volta na pilha
	alta = lVal >> 32;
	baixa = lVal & 0xffffffff;
	push(alta);
	push(baixa);

	atualizaPc();
}

/**
 * @brief Desempilha quantidade a ser shiftada. Desempilha valor inteiro a ser shiftado
 * shifta-o a direita e empilha o resultado
 * OBS: shifta no maximo 32 bits. Sem sinal -> operador >>
 * @return void
 */
void iushr()
{
	// Pega quantidade a ser shiftada e limita em 32 bits (0x1f)
	int32_t shift = pop_op();
	shift = shift & 0x1f;

	// Obtem valor da pilha e shifta a esquerda
	int32_t sVal = pop_op();
	sVal = sVal >> shift;
	push(sVal); // Empilha o resultado

	atualizaPc();
}

/**
 * @brief Desempilha quantidade a ser shiftada. Desempilha valor long a ser shiftado
 * shifta-o a direita e empilha o resultado
 * OBS: shifta no maximo 64 bits. Sem sinal -> operador >>
 * @return void
 */
void lushr()
{
	// Desempilha a quantidade a ser shiftada e limita em 64 bits
	int32_t shift = pop_op();
	shift = shift & 0x3f;

	int32_t baixa, alta;
	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(long)

	int64_t lVal = alta; // Atribui parte alta primeiro
	lVal <<= 32;				 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	lVal = lVal + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	lVal = lVal >> shift; // Shifta

	// Converte para parte alta e baixa novamente para empilhar
	alta = lVal >> 32;
	baixa = lVal & 0xffffffff;

	// Empilha
	push(alta);
	push(baixa);

	atualizaPc();
}

/**
 * @brief Funcao desempilha dois valores inteiros, opera com o and e empilha resultado
 * @param void
 * @return void
 */
void iand()
{
	int32_t pop1 = pop_op();
	int32_t pop2 = pop_op();
	int32_t aux = pop1 & pop2; // And

	push(aux); // Empilha

	frameCorrente->pc++; // atualiza pc
}

/**
 * @brief Funcao desempilha dois valores long, opera com o and e empilha resultado
 * @param void
 * @return void
 */
void land()
{
	int32_t baixa, alta;

	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(long)

	int64_t lVal = alta; // Atribui parte alta primeiro
	lVal <<= 32;				 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	lVal = lVal + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(long)

	int64_t lVal1 = alta;	 // Atribui parte alta primeiro
	lVal1 <<= 32;					 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	lVal1 = lVal1 + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	int64_t resultado = lVal1 & lVal; // And

	// Converte para parte alta e baixa novamente para empilhar
	alta = resultado >> 32;
	baixa = resultado & 0xffffffff;

	// Empilha
	push(alta);
	push(baixa);

	atualizaPc();
}

/**
 * @brief Funcao desempilha dois valores inteiros, opera com o or e empilha resultado
 * @param void
 * @return void
 */
void ior()
{
	int32_t pop1 = pop_op();
	int32_t pop2 = pop_op();
	int32_t aux = pop1 | pop2; // Or
	push(aux);								 // Empilha

	frameCorrente->pc++; // atualiza pc
}

/**
 * @brief Funcao desempilha dois valores long, opera com o or e empilha resultado
 * @param void
 * @return void
 */
void lor()
{
	int32_t baixa, alta;

	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(long)

	int64_t lVal = alta; // Atribui parte alta primeiro
	lVal <<= 32;				 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	lVal = lVal + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(long)

	int64_t lVal1 = alta;	 // Atribui parte alta primeiro
	lVal1 <<= 32;					 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	lVal1 = lVal1 + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	int64_t resultado = lVal1 | lVal; // Or

	// Converte para parte alta e baixa novamente para empilhar
	alta = resultado >> 32;
	baixa = resultado & 0xffffffff;

	// Empilha
	push(alta);
	push(baixa);

	inicializa_decodificador(dec);
	int num_bytes = dec[frameCorrente->code[frameCorrente->pc]].bytes;

	atualizaPc(); // atualiza pc
}

/**
 * @brief Funcao desempilha dois valores inteiros, opera com o xor e empilha resultado
 * @param void
 * @return void
 */
void ixor()
{
	int32_t pop1 = pop_op();
	int32_t pop2 = pop_op();
	int32_t aux = pop1 ^ pop2; // Xor
	push(aux);								 // Empilha

	frameCorrente->pc++; // atualiza pc
}

/**
 * @brief Funcao desempilha dois valores long, opera com o xor e empilha resultado
 * @param void
 * @return void
 */
void lxor()
{
	int32_t baixa, alta;

	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(long)

	int64_t lVal = alta; // Atribui parte alta primeiro
	lVal <<= 32;				 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	lVal = lVal + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(long)

	int64_t lVal1 = alta;	 // Atribui parte alta primeiro
	lVal1 <<= 32;					 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	lVal1 = lVal1 + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	int64_t resultado = lVal1 ^ lVal; // Xor

	// Converte para parte alta e baixa novamente para empilhar
	alta = resultado >> 32;
	baixa = resultado & 0xffffffff;

	// Empilha
	push(alta);
	push(baixa);

	atualizaPc();
}

/**
 * @brief Funcao incrementa um valor do array de variaveis locais por uma constante.
 * @param void
 * @return void
 */
void iinc()
{
	int8_t field = frameCorrente->code[frameCorrente->pc + 1];		// Pega posicao no array de var local
	int32_t value = frameCorrente->fields[field];									// Pega valor a ser incrementado do array de var local
	int8_t constant = frameCorrente->code[frameCorrente->pc + 2]; // Pega a constante a ser somada

	int8_t sumVal = (int8_t)value; // Faz o cast para 8bits
	sumVal = sumVal + constant;		 // Soma a constante

	frameCorrente->fields[field] = (int32_t)sumVal; // Atualiza o valor somado no array

	atualizaPc();
}

/**
 * @brief Funcao que desempilha um inteiro da pilha, converte para um longt e empilha
 * o resultado
 * @param void
 * @return void
 */
void i2l()
{
	char *tipo = "L";
	tipoGlobal = tipo;
	int32_t alta, baixa;

	int32_t val = pop_op(); // pega inteiro

	// transforma para long
	int64_t long_num = (int64_t)val;
	alta = long_num >> 32;
	baixa = long_num & 0xffffffff;

	// empilha long
	push(alta);
	push(baixa);

	atualizaPc();
}

/**
 * @brief Funcao que desempilha um inteiro da pilha, converte para um float e empilha
 * o resultado
 * @param void
 * @return void
 */
void i2f()
{
	char *tipo = "F";
	tipoGlobal = tipo;

	int32_t val = (int32_t)pop_op(); // Obtem valor da pilha
	float valF = (float)val;				 // Realiza cast para float

	// Utiliza um auxiliar para armazenar o valor float e empilha-lo
	int32_t valPilha;
	memcpy(&valPilha, &valF, sizeof(int32_t));

	push(valPilha);

	atualizaPc();
}

/**
 * @brief Desempilha um inteiro converte para double e empilha o resultado
 * @param void
 * @return void
 */
void i2d()
{
	char *tipo = "D";
	tipoGlobal = tipo;

	int32_t retPilha = pop_op();		// Desempilha valor da pilha
	double dVal = (double)retPilha; // Cast para double

	int64_t pilhaVal;
	memcpy(&pilhaVal, &dVal, sizeof(int64_t)); // Copia bytes em doubleNum para pilhaVal que e um int64

	// Parte alta e parte baixa do double
	int32_t alta;
	int32_t baixa;

	alta = pilhaVal >> 32;				 // Shifta 32 bits para pegar somente a parte alta
	baixa = pilhaVal & 0xffffffff; // Realiza um and bit a bit para zerar a parte alta e obter somente a parte baixa

	// Empilha parte alta e baixa
	push(alta);
	push(baixa);

	atualizaPc();
}

/**
 * @brief Desempilha um long converte para int e empilha
 * @param void
 * @return void
 */
void l2i()
{
	char *tipo = "I";
	tipoGlobal = tipo;
	int32_t alta, baixa;

	baixa = pop_op();
	alta = pop_op();

	// Empilha somente a parte baixa - 32 bits perdendo precisao
	push(baixa);
	atualizaPc();
}

/**
 * @brief Desempilha um long converte para float e empilha
 * @param void
 * @return void
 */
void l2f()
{
	char *tipo = "F";
	tipoGlobal = tipo;

	int32_t baixa, alta;
	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(long)

	int64_t lVal = alta; // Atribui parte alta primeiro
	lVal <<= 32;				 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	lVal = lVal | baixa; // Preenche os 32 bits inferiores com a parte baixa

	float fVal;
	fVal = (float)lVal;

	int32_t valPilha;
	memcpy(&valPilha, &fVal, sizeof(int32_t));

	push(valPilha);

	atualizaPc();
}

/**
 * @brief Desempilha um long converte para double e empilha
 * @param void
 * @return void
 */
void l2d()
{
	char *tipo = "D";
	tipoGlobal = tipo;

	int32_t baixa, alta;
	baixa = pop_op();
	alta = pop_op();

	// Converter os numeros 32 bits para 64 bits(long)

	int64_t lVal = alta; // Atribui parte alta primeiro
	lVal <<= 32;				 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	lVal = lVal + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	double dVal;
	memcpy(&dVal, &lVal, sizeof(double));

	int64_t valorPilha; // Converte mais uma vez o double para int64 para empilhar corretamente
	memcpy(&valorPilha, &dVal, sizeof(int64_t));

	// Converte para parte alta e baixa novamente para empilhar
	alta = valorPilha >> 32;
	baixa = valorPilha & 0xffffffff;

	// Empilha
	push(alta);
	push(baixa);

	atualizaPc();
}

/**
 * @brief Desempilha um float converte para int e empilha
 * @param void
 * @return void
 */
void f2i()
{
	char *tipo = "I";
	tipoGlobal = tipo;

	int32_t retPilha = pop_op();

	float fVal;
	memcpy(&fVal, &retPilha, sizeof(int32_t));
	push((int32_t)fVal);
	atualizaPc();
}

/**
 * @brief Desempilha um float converte para long e empilha
 * @param void
 * @return void
 */
void f2l()
{
	char *tipo = "L";
	tipoGlobal = tipo;

	int32_t retPilha = pop_op(); // Desempilha valor da pilha

	float fVal;
	memcpy(&fVal, &retPilha, sizeof(int32_t)); // Copia os bytes do retPilha para uma var float - Nao perder precisao
	int64_t lVal = (int64_t)fVal;

	// Parte alta e parte baixa do double
	int32_t alta;
	int32_t baixa;

	alta = lVal >> 32; // Shifta 32 bits para pegar somente a parte alta

	baixa = lVal & 0xffffffff; // Realiza um and bit a bit para zerar a parte alta e obter somente a parte baixa

	// Empilha parte alta e baixa
	push(alta);
	push(baixa);

	atualizaPc();
}

/**
 * @brief Desempilha um float converte para double e empilha
 * @param void
 * @return void
 */
void f2d()
{
	char *tipo = "D";
	tipoGlobal = tipo;

	int32_t retPilha = pop_op(); // Desempilha valor da pilha
	float fVal;

	memcpy(&fVal, &retPilha, sizeof(int32_t)); // Copia os bytes do retPilha para uma var float -> Nao perder precisao

	double dVal = (double)fVal; // Cast para double

	int64_t pilhaVal; // Copia dVal para um int64_t para poder empilhar. -> Nao perder precisao
	memcpy(&pilhaVal, &dVal, 2 * sizeof(int32_t));

	// Parte alta e parte baixa do double
	int32_t alta;
	int32_t baixa;

	alta = pilhaVal >> 32;				 // Shifta 32 bits para pegar somente a parte alta
	baixa = pilhaVal & 0xffffffff; // Realiza um and bit a bit para zerar a parte alta e obter somente a parte baixa

	// Empilha parte alta e baixa
	push(alta);
	push(baixa);

	atualizaPc();
}

/**
 * @brief Desempilha um double converte para integer e empilha
 * @param void
 * @return void
 */
void d2i()
{
	char *tipo = "I";
	tipoGlobal = tipo;

	int32_t baixa, alta;
	baixa = pop_op();
	alta = pop_op();

	int64_t dVal = alta; // Atribui parte alta primeiro
	dVal <<= 32;				 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	dVal = dVal + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	// Copia os bytes do int64_t para um double (memcpy copia 64 bits de dVal para v1)
	// Nao perder a precisao - Alternativa UNION
	double v1;
	memcpy(&v1, &dVal, sizeof(double));

	push((int32_t)v1);
	atualizaPc();
}

/**
 * @brief Desempilha um double converte para long(64bits) e empilha
 * @param void
 * @return void
 */
void d2l()
{
	char *tipo = "L";
	tipoGlobal = tipo;

	int32_t baixa, alta;
	baixa = pop_op();
	alta = pop_op();

	int64_t dVal = alta; // Atribui parte alta primeiro

	dVal <<= 32;				 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	dVal = dVal + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	// Copia os bytes do int64_t para um double (memcpy copia 64 bits de dVal para v1)
	// Nao perder a precisao - Alternativa UNION
	double v1;
	memcpy(&v1, &dVal, sizeof(double));

	int64_t long_num = (int64_t)v1;
	alta = long_num >> 32;
	baixa = long_num & 0xffffffff;

	// Empilha
	push(alta);
	push(baixa);
	atualizaPc();
}

/**
 * @brief Desempilha um double converte para float e empilha
 * @param void
 * @return void
 */
void d2f()
{
	char *tipo = "F";
	tipoGlobal = tipo;

	int32_t alta, baixa;
	baixa = pop_op();
	alta = pop_op();

	int64_t dVal = alta; // Atribui parte alta primeiro

	dVal <<= 32; // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	// Preenche os 32 bits inferiores com a parte baixa. -> Basta somar pois
	// os 32 bits da parte baixa estao zerados
	dVal = dVal + baixa;

	// Copia os bytes do int64_t para um double (memcpy copia 64 bits de dVal para v1)
	// Nao perder a precisao - Alternativa UNION
	double v1;
	memcpy(&v1, &dVal, sizeof(double));

	float fVal = (float)v1; // Realiza cast

	int32_t pilhaVal; // Copia valor castado para um int32_T para ser empilhado.
	memcpy(&pilhaVal, &fVal, sizeof(float));

	push(pilhaVal);

	atualizaPc();
}

/**
 * @brief Desempilha um inteiro converte para byte e empilha
 * pode perder precisao 32bits -> 8bits
 * @param void
 * @return void
 */
void i2b()
{
	int32_t valPilha = pop_op();		// Obtem valor de 32 bits da pilha
	int8_t bVal = (int8_t)valPilha; // Converte para byte (pode perder precisao)
	push((int32_t)bVal);						// Empilha novamente fazendo cast para 32bits para se adequar a pilha
	atualizaPc();
}

/**
 * @brief Desempilha um inteiro converte para char e empilha
 * pode perder precisao 32bits -> 16bits
 * @param void
 * @return void
 */
void i2c()
{
	char *tipo = "C";
	tipoGlobal = tipo;

	int32_t valPilha = pop_op();			// Obtem valor de 32 bits da pilha
	int16_t cVal = (int16_t)valPilha; // Converte para char (pode perder precisao)
	push((int32_t)cVal);							// Empilha novamente fazendo cast para 32bits para se adequar a pilha
	atualizaPc();
}

/**
 * @brief Desempilha um inteiro converte para short e empilha
 * pode perder precisao 32bits -> 16bits
 * @param void
 * @return void
 */
void i2s()
{
	int32_t valPilha = pop_op();			// Obtem valor de 32 bits da pilha
	int16_t cVal = (int16_t)valPilha; // Converte para char (pode perder precisao)
	push((int32_t)cVal);							// Empilha novamente fazendo cast para 32bits para se adequar a pilha
	atualizaPc();
}

/**
 * @brief Funcao que desempilha dois longs da pilha e compara
 * Se primeiro maior que segundo -> empilha 1
 * Se forem iguais               -> empilha 0
 * Se primeiro menor que segundo -> empilha -1
 * @param void
 * @return void
 */
void lcmp()
{
	int32_t baixa, alta;
	baixa = pop_op();
	alta = pop_op();

	int64_t lVal = alta; // Atribui parte alta primeiro
	lVal <<= 32;				 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	lVal = lVal + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	baixa = pop_op();
	alta = pop_op();

	int64_t lVal2 = alta;	 // Atribui parte alta primeiro
	lVal2 <<= 32;					 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	lVal2 = lVal2 + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	// Compara os dois longs e seta o resultado
	if (lVal2 == lVal)
	{
		push((int32_t)0);
	}
	else if (lVal2 > lVal)
	{
		push((int32_t)1);
	}
	else if (lVal2 < lVal)
	{
		push((int32_t)-1);
	}

	atualizaPc();
}

/**
 * @brief Funcao que desempilha dois floats da pilha e compara
 * Se primeiro maior que segundo -> empilha 1
 * Se forem iguais               -> empilha 0
 * Se primeiro menor que segundo -> empilha -1
 * OBS: Difere do fcmpg somente no tratamento do caso NaN
 * @param void
 * @return void
 */
void fcmpl()
{
	float val1, val2; // Valores a serem comparadas
	int32_t retPilha; // Valor para receber o pop da pilha e realizar a copia dos bytes para os floats

	retPilha = pop_op();										 // Desempilha o segundo valor(topo)
	memcpy(&val2, &retPilha, sizeof(float)); // Copia os bytes do int32 para uma var do tipo float para nao perder precisao

	retPilha = pop_op();										 // Desempilha o primeiro valor(topo)
	memcpy(&val1, &retPilha, sizeof(float)); // Copia os bytes do int32 para uma var do tipo float para nao perder precisao

	// Compara os dois floats e seta o resultado
	if (val1 == val2)
	{
		push((int32_t)0);
	}
	else if (val1 > val2)
	{
		push((int32_t)1);
	}
	else if (val1 < val2)
	{
		push((int32_t)-1);
	}
	else
	{
		printf("NaN!!\n");
		push((int32_t)-1);
	}

	atualizaPc();
}

/**
 * @brief Funcao que desempilha dois floats da pilha e compara
 * Se primeiro maior que segundo -> empilha 1
 * Se forem iguais               -> empilha 0
 * Se primeiro menor que segundo -> empilha -1
 * OBS: Difere do fcmpl somente no tratamento do caso NaN
 * @param void
 * @return void
 */
void fcmpg()
{
	float val1, val2; // Valores a serem comparadas
	int32_t retPilha; // Valor para receber o pop da pilha e realizar a copia dos bytes para os floats

	retPilha = pop_op();										 // Desempilha o segundo valor(topo)
	memcpy(&val2, &retPilha, sizeof(float)); // Copia os bytes do int32 para uma var do tipo float para nao perder precisao

	retPilha = pop_op();										 // Desempilha o primeiro valor(topo)
	memcpy(&val1, &retPilha, sizeof(float)); // Copia os bytes do int32 para uma var do tipo float para nao perder precisao

	// Compara os dois floats e seta o resultado
	if (val1 == val2)
	{
		push((int32_t)0);
	}
	else if (val1 > val2)
	{
		push((int32_t)1);
	}
	else if (val1 < val2)
	{
		push((int32_t)-1);
	}
	else
	{
		printf("NaN!!\n");
		push((int32_t)1);
	}

	atualizaPc();
}

/**
 * @brief Funcao que desempilha dois double da pilha e compara
 * Se primeiro maior que segundo -> empilha 1
 * Se forem iguais               -> empilha 0
 * Se primeiro menor que segundo -> empilha -1
 * OBS: Difere do dcmpg somente no tratamento do caso NaN
 * @param void
 * @return void
 */
void dcmpl()
{
	int32_t baixa, alta;
	baixa = pop_op();
	alta = pop_op();

	int64_t dVal = alta; // Atribui parte alta primeiro
	dVal <<= 32;				 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	dVal = dVal + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	double doubleCmpl;
	memcpy(&doubleCmpl, &dVal, sizeof(double));

	baixa = pop_op();
	alta = pop_op();

	int64_t dVal2 = alta;	 // Atribui parte alta primeiro
	dVal2 <<= 32;					 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	dVal2 = dVal2 + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	double doubleCmpl2;
	memcpy(&doubleCmpl2, &dVal2, sizeof(double));

	// Compara os dois longs e seta o resultado
	if (doubleCmpl2 > doubleCmpl)
	{
		push((int32_t)1);
	}
	else if (doubleCmpl2 == doubleCmpl)
	{
		push((int32_t)0);
	}
	else if (doubleCmpl2 < doubleCmpl)
	{
		push((int32_t)-1);
	}
	else
	{
		printf("NaN!\n");
		push((int32_t)-1);
	}

	atualizaPc();
}

/**
 * @brief Funcao que desempilha dois double da pilha e compara
 * Se primeiro maior que segundo -> empilha 1
 * Se forem iguais               -> empilha 0
 * Se primeiro menor que segundo -> empilha -1
 * OBS: Difere do dcmpl somente no tratamento do caso NaN!
 * @param void
 * @return void
 */
void dcmpg()
{
	int32_t baixa, alta;
	baixa = pop_op();
	alta = pop_op();

	int64_t dVal = alta; // Atribui parte alta primeiro
	dVal <<= 32;				 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	dVal = dVal + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	double doubleCmpl;
	memcpy(&doubleCmpl, &dVal, sizeof(double));

	baixa = pop_op();
	alta = pop_op();

	int64_t dVal2 = alta;	 // Atribui parte alta primeiro
	dVal2 <<= 32;					 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
	dVal2 = dVal2 + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

	double doubleCmpl2;
	memcpy(&doubleCmpl2, &dVal2, sizeof(double));

	// Compara os dois longs e seta o resultado
	if (doubleCmpl2 > doubleCmpl)
	{
		push((int32_t)1);
	}
	else if (doubleCmpl2 == doubleCmpl)
	{
		push((int32_t)0);
	}
	else if (doubleCmpl2 < doubleCmpl)
	{
		push((int32_t)-1);
	}
	else
	{
		printf("NaN!\n");
		push((int32_t)1);
	}

	atualizaPc();
}

/**
 * @brief Funcao que realiza um jump se valor desempilhado for igual que 0
 * eq -> equals to zero
 * @param void
 * @return void
 */
void ifeq()
{
	uint8_t offset1, offset2;
	int16_t offset;

	// Pega offset para salto
	offset1 = frameCorrente->code[frameCorrente->pc + 1];
	offset2 = frameCorrente->code[frameCorrente->pc + 2];
	offset = offset1;
	offset <<= 8;
	offset |= offset2;

	// Pega valor a ser comparado na pilha
	int32_t retPilha = pop_op();

	// Se val igual a zero atualiza pc com offset
	if (retPilha == 0)
	{
		frameCorrente->pc += offset;
	}
	else
	{
		frameCorrente->pc += 3;
	}
}

/**
 * @brief Funcao que realiza um jump se valor desempilhado for diferente de 0
 * ne -> not equal to zero
 * @param void
 * @return void
 */
void ifne()
{
	uint8_t offset1, offset2;
	int16_t offset;

	// Pega offset para salto
	offset1 = frameCorrente->code[frameCorrente->pc + 1];
	offset2 = frameCorrente->code[frameCorrente->pc + 2];
	offset = offset1;
	offset <<= 8;
	offset |= offset2;

	int32_t retPilha = pop_op(); // Pega valor a ser comparado na pilha

	// Se val diferente de zero atualiza pc com offset
	if (retPilha != 0)
	{
		frameCorrente->pc += offset;
	}
	else
	{
		frameCorrente->pc += 3;
	}
}

/**
 * @brief Funcao que realiza um jump se valor desempilhado for menor que 0
 * lt -> lower than zero
 * @param void
 * @return void
 */
void iflt()
{
	uint8_t offset1, offset2;
	int16_t offset;

	// Pega offset para salto
	offset1 = frameCorrente->code[frameCorrente->pc + 1];
	offset2 = frameCorrente->code[frameCorrente->pc + 2];
	offset = offset1;
	offset <<= 8;
	offset |= offset2;

	int32_t retPilha = pop_op(); // Pega valor a ser comparado na pilha

	// Se val menor que zero atualiza pc com offset
	if (retPilha < 0)
	{
		frameCorrente->pc += offset;
	}
	else
	{
		frameCorrente->pc += 3;
	}
}

/**
 * @brief Funcao que realiza um jump se valor desempilhado for maior ou igual que 0
 * ge -> greater than or equals to zero
 * @param void
 * @return void
 */
void ifge()
{
	uint8_t offset1, offset2;
	int16_t offset;

	// Pega offset para salto
	offset1 = frameCorrente->code[frameCorrente->pc + 1];
	offset2 = frameCorrente->code[frameCorrente->pc + 2];
	offset = offset1;
	offset <<= 8;
	offset |= offset2;

	int32_t retPilha = pop_op(); // Pega valor a ser comparado na pilha

	// Se val maior ou igual que zero atualiza pc com offset
	if (retPilha >= 0)
	{
		frameCorrente->pc += offset;
	}
	else
	{
		frameCorrente->pc += 3;
	}
}

/**
 * @brief Funcao que realiza um jump se valor desempilhado for maior que 0
 * gt -> greater than to zero
 * @param void
 * @return void
 */
void ifgt()
{
	uint8_t offset1, offset2;
	int16_t offset;

	// Pega offset para salto
	offset1 = frameCorrente->code[frameCorrente->pc + 1];
	offset2 = frameCorrente->code[frameCorrente->pc + 2];
	offset = offset1;
	offset <<= 8;
	offset |= offset2;

	int32_t retPilha = pop_op(); // Pega valor a ser comparado na pilha

	// Se val maior que zero atualiza pc com offset
	if (retPilha > 0)
	{
		frameCorrente->pc += offset;
	}
	else
	{
		frameCorrente->pc += 3;
	}
}

/**
 * @brief Funcao que realiza um jump se valor desempilhado for menor ou igual que 0
 * gt -> greater than to zero
 * @param void
 * @return void
 */
void ifle()
{
	uint8_t offset1, offset2;
	int16_t offset;

	// Pega offset para salto
	offset1 = frameCorrente->code[frameCorrente->pc + 1];
	offset2 = frameCorrente->code[frameCorrente->pc + 2];
	offset = offset1;
	offset <<= 8;
	offset |= offset2;

	int32_t retPilha = pop_op(); // Pega valor a ser comparado na pilha

	// Se val menor ou igual que zero atualiza pc com offset
	if (retPilha <= 0)
	{
		frameCorrente->pc += offset;
	}
	else
	{
		frameCorrente->pc += 3;
	}
}

/**
 * @brief Funcao que realiza um jump se os dois valores da pilha de operandos
 * forem iguais
 * @param void
 * @return void
 */
void if_icmpeq()
{
	uint8_t offset1, offset2;
	int16_t offset;

	// Pega offset para salto
	offset1 = frameCorrente->code[frameCorrente->pc + 1];
	offset2 = frameCorrente->code[frameCorrente->pc + 2];
	offset = offset1;
	offset <<= 8;
	offset |= offset2;

	// Pega valor a ser comparado na pilha
	int32_t retPilha1 = pop_op();
	int32_t retPilha2 = pop_op();

	// Se val menor ou igual que zero atualiza pc com offset
	if (retPilha1 == retPilha2)
	{
		frameCorrente->pc += offset;
	}
	else
	{
		frameCorrente->pc += 3;
	}
}

/**
 * @brief Funcao que realiza um jump se os dois valores da pilha de operandos
 * nao forem iguais
 * @param void
 * @return void
 */
void if_icmpne()
{
	uint8_t offset1, offset2;
	int16_t offset;

	// Pega offset para salto
	offset1 = frameCorrente->code[frameCorrente->pc + 1];
	offset2 = frameCorrente->code[frameCorrente->pc + 2];
	offset = offset1;
	offset <<= 8;
	offset |= offset2;

	// Pega valor a ser comparado na pilha
	int32_t retPilha1 = pop_op();
	int32_t retPilha2 = pop_op();

	// Se val menor ou igual que zero atualiza pc com offset
	if (retPilha1 != retPilha2)
	{
		frameCorrente->pc += offset;
	}
	else
	{
		frameCorrente->pc += 3;
	}
}

/**
 * @brief Funcao que realiza um jump se um valor da pilha for menor que o outro
 * .
 * @param void
 * @return void
 */
void if_icmplt()
{
	uint8_t offset1, offset2;
	int16_t offset;

	// Pega offset para salto
	offset1 = frameCorrente->code[frameCorrente->pc + 1];
	offset2 = frameCorrente->code[frameCorrente->pc + 2];
	offset = offset1;
	offset <<= 8;
	offset |= offset2;

	// Pega valor a ser comparado na pilha
	int32_t retPilha1 = pop_op();
	int32_t retPilha2 = pop_op();

	// Se val menor ou igual que zero atualiza pc com offset
	if (retPilha2 < retPilha1)
	{
		frameCorrente->pc += offset;
	}
	else
	{
		frameCorrente->pc += 3;
	}
}

/**
 * @brief Funcao que realiza um jump se um valor da pilha for maior ou igual
 * que o outro
 * @param void
 * @return void
 */
void if_icmpge()
{
	uint8_t offset1, offset2;
	int16_t offset;

	// Pega offset para salto
	offset1 = frameCorrente->code[frameCorrente->pc + 1];
	offset2 = frameCorrente->code[frameCorrente->pc + 2];
	offset = offset1;
	offset <<= 8;
	offset |= offset2;

	// Pega valor a ser comparado na pilha
	int32_t retPilha1 = pop_op();
	int32_t retPilha2 = pop_op();

	// Se val menor ou igual que zero atualiza pc com offset
	if (retPilha2 >= retPilha1)
	{
		frameCorrente->pc += offset;
	}
	else
	{
		frameCorrente->pc += 3;
	}
}

/**
 * @brief Funcao que realiza um jump se um valor da pilha for maior
 * que o outro
 * @param void
 * @return void
 */
void if_icmpgt()
{
	uint8_t offset1, offset2;
	int16_t offset;

	// Pega offset para salto
	offset1 = frameCorrente->code[frameCorrente->pc + 1];
	offset2 = frameCorrente->code[frameCorrente->pc + 2];
	offset = offset1;
	offset <<= 8;
	offset |= offset2;

	// Pega valor a ser comparado na pilha
	int32_t retPilha1 = pop_op();
	int32_t retPilha2 = pop_op();

	// Se val menor ou igual que zero atualiza pc com offset
	if (retPilha2 > retPilha1)
	{
		frameCorrente->pc += offset;
	}
	else
	{
		frameCorrente->pc += 3;
	}
}

/**
 * @brief Funcao que realiza um jump se um valor da pilha for menor ou igual
 * que o outro
 * @param void
 * @return void
 */
void if_icmple()
{
	uint8_t offset1, offset2;
	int16_t offset;

	// Pega offset para salto
	offset1 = frameCorrente->code[frameCorrente->pc + 1];
	offset2 = frameCorrente->code[frameCorrente->pc + 2];
	offset = offset1;
	offset <<= 8;
	offset |= offset2;

	// Pega valor a ser comparado na pilha
	int32_t retPilha1 = pop_op();
	int32_t retPilha2 = pop_op();

	// Se val menor ou igual que zero atualiza pc com offset
	if (retPilha2 <= retPilha1)
	{
		frameCorrente->pc += offset;
	}
	else
	{
		frameCorrente->pc += 3;
	}
}

/**
 * @brief Funcao que realiza um jump se um valor da pilha for igual
 * que o outro
 * @param void
 * @return void
 */
void if_acmpeq()
{
	uint8_t offset1, offset2;
	int16_t offset;

	// Pega offset para salto
	offset1 = frameCorrente->code[frameCorrente->pc + 1];
	offset2 = frameCorrente->code[frameCorrente->pc + 2];
	offset = offset1;
	offset <<= 8;
	offset |= offset2;

	// Pega valor a ser comparado na pilha
	int32_t retPilha1 = pop_op();
	int32_t retPilha2 = pop_op();

	// Se val menor ou igual que zero atualiza pc com offset
	if (retPilha2 == retPilha1)
	{
		frameCorrente->pc += offset;
	}
	else
	{
		frameCorrente->pc += 3;
	}
}

/**
 * @brief Funcao que realiza um jump se um valor da pilha for diferente
 * do outro
 * @param void
 * @return void
 */
void if_acmpne()
{
	uint8_t offset1, offset2;
	int16_t offset;

	// Pega offset para salto
	offset1 = frameCorrente->code[frameCorrente->pc + 1];
	offset2 = frameCorrente->code[frameCorrente->pc + 2];
	offset = offset1;
	offset <<= 8;
	offset |= offset2;

	// Pega valor a ser comparado na pilha
	int32_t retPilha1 = pop_op();
	int32_t retPilha2 = pop_op();

	// Se val menor ou igual que zero atualiza pc com offset
	if (retPilha2 != retPilha1)
	{
		frameCorrente->pc += offset;
	}
	else
	{
		frameCorrente->pc += 3;
	}
}

/**
 * @brief Funcao que realiza um jump a partir de um offset da instrucao
 * @param void
 * @return void
 */
void ins_goto()
{
	// obtem offset que vem da instrucao
	uint8_t offset1, offset2;
	int16_t offset;

	// Pega offset para salto
	offset1 = frameCorrente->code[frameCorrente->pc + 1];
	offset2 = frameCorrente->code[frameCorrente->pc + 2];
	offset = offset1;
	offset <<= 8;
	offset |= offset2;

	// Jump
	frameCorrente->pc += offset;
}

/**
 * @brief Jump SubRoutine. Pula para regiao formada por dois offsets
 * salva na pilha endereco de retorno da proxima instrucao
 * @param void
 * @return void
 */
void jsr()
{
	// Salva na pilha endereco de retorno(Instrucao seguinte ao jsr)
	push(frameCorrente->pc + 3);

	// obtem offset que vem da instrucao
	uint8_t offset1, offset2;
	int16_t offset;

	// Pega offset para salto
	offset1 = frameCorrente->code[frameCorrente->pc + 1];
	offset2 = frameCorrente->code[frameCorrente->pc + 2];
	offset = offset1;
	offset <<= 8;
	offset |= offset2;

	// Jump
	frameCorrente->pc += offset;
}

void ret()
{
}

/**
 * @brief Funcao que realiza a operacao de switch. Com valores variados
 * @param void
 * @return void
 */
void tableswitch()
{
	uint32_t bytes_preench;
	int32_t indice;
	int32_t default_v, low, high, npairs;
	uint32_t pc_novo, pc_aux;
	int32_t qtd_offset, offset, posicao;
	uint32_t temp;

	bool definido = false;			// diz se o novo valor de pc ja esta definido ou nao
	pc_aux = frameCorrente->pc; // pc auxiliar que iremos seguindo durante a execucao da instrucao
	indice = pop_op();					// pega indice da operand stack

	/**
	 * Passo 1 - le ate o low, se o indice eh menor que low - define logo o novo valor para PC
	 */
	// pula bytes de preenchimento
	bytes_preench = (4 - ((pc_aux + 1) % 4)) % 4;
	pc_aux += bytes_preench;
	pc_aux++;

	// pega bytes do target default
	default_v = 0;
	for (int l = 0; l < 4; l++)
	{
		default_v = (default_v << 8) + frameCorrente->code[pc_aux];
		pc_aux++;
	}

	// pega bytes low
	low = 0;
	for (int l = 0; l < 4; l++)
	{
		low = (low << 8) + frameCorrente->code[pc_aux];
		pc_aux++;
	}

	// se o indice eh menor que o low e ainda nao definimos novo pc
	if (indice < low && !definido)
	{
		definido = true;
		pc_novo = frameCorrente->pc + default_v;
	}

	/**
	 * Passo 2 - le ateh o high. Se o indice eh maior que o high - define o novo valor para PC
	 * caso low ainda nao tenha sido definido
	 */
	// pega bytes high
	high = 0;
	for (int l = 0; l < 4; l++)
	{
		high = (high << 8) + frameCorrente->code[pc_aux];
		pc_aux++;
	}

	// Se o indice eh maior que o high e ainda nao definimos novo pc
	if (indice > high && !definido)
	{
		definido = true;
		pc_novo = frameCorrente->pc + default_v;
	}

	/**
	 * Passo 3 - calcula offset na posicao index - low. Coloca novo endereco de PC aqui,
	 * caso ainda nao tenha sido definido
	 */
	qtd_offset = 1 + high - low;
	posicao = indice - low;
	for (int32_t l = 0; l < qtd_offset; l++)
	{
		// se estamos na posicao correta
		if (l == posicao)
		{
			// extrai offset
			offset = 0;
			for (int i = 0; i < 4; i++)
			{
				offset = (offset << 8) + frameCorrente->code[pc_aux];
				pc_aux++;
			}

			// calcula posicao
			pc_novo = frameCorrente->pc + offset;
			definido = true;

			// sai do loop
			break;
		}

		// senao, passa pelo offset atual incrementando pc
		else
		{
			for (int i = 0; i < 4; i++)
			{
				pc_aux++;
			}
		}
	}

	frameCorrente->pc = pc_novo; // poe valor correto em frameCorrente
}

/**
 * @brief Funcao que realiza a operacao de switch. Com valores sequenciais
 * @param void
 * @return void
 */
void lookupswitch()
{
	uint32_t pc_aux, pc_novo;
	uint32_t bytes_preench;
	uint32_t offset;
	int32_t default_v, npairs;
	int32_t match;
	int32_t key;

	bool definido = false;			// diz se o novo valor de pc ja esta definido ou nao
	pc_aux = frameCorrente->pc; // pc auxiliar que iremos seguindo durante a execucao da instrucao
	key = pop_op();							// pega key da operand stack

	// pula bytes de preenchimento
	bytes_preench = (4 - ((pc_aux + 1) % 4)) % 4;
	pc_aux += bytes_preench;
	pc_aux++;

	// pega bytes default
	default_v = 0;
	for (int l = 0; l < 4; l++)
	{
		default_v = (default_v << 8) + frameCorrente->code[pc_aux];
		pc_aux++;
	}

	// pega numeros de pares
	npairs = 0;
	for (int l = 0; l < 4; l++)
	{
		npairs = (npairs << 8) + frameCorrente->code[pc_aux];
		pc_aux++;
	}

	// itera pelo numero de pares
	for (int32_t l = 0; l < npairs; l++)
	{
		// pega match atual
		match = 0;
		for (int l = 0; l < 4; l++)
		{
			match = (match << 8) + frameCorrente->code[pc_aux];
			pc_aux++;
		}

		// se a key corresponde ao match
		if (key == match)
		{
			// pega offset
			offset = 0;
			for (int l = 0; l < 4; l++)
			{
				offset = (offset << 8) + frameCorrente->code[pc_aux];
				pc_aux++;
			}

			// poe valor correto em pc_novo
			pc_novo = frameCorrente->pc + offset;

			// set booleano que achou o match
			definido = true;
		}

		// senao
		else
		{
			// pula offset
			for (int i = 0; i < 4; i++)
			{
				pc_aux++;
			}
		}
	}

	// se ainda nao achamos o offset
	if (!definido)
	{
		pc_novo = frameCorrente->pc + default_v;
	}

	frameCorrente->pc = pc_novo; // poe valor correto no offset
}

/**
 * @brief Retira um valor da pilha(inteiro) e empilha no frame chamador
 * @param void
 * @return void
 */
void ireturn()
{
	retorno = pop_op();
	flagRet = 1;

	frameCorrente->pc = frameCorrente->code_length + 1;
}

/**
 * @brief Retira dois valores da pilha(long) e empilha na funcao chamadora
 * @param void
 * @return void
 */
void lreturn()
{
	int32_t alta, baixa;

	baixa = pop_op();
	alta = pop_op();

	flagRet = 2;

	retAlta = alta;
	retBaixa = baixa;

	frameCorrente->pc = frameCorrente->code_length + 1;
}

/**
 * @brief Retira um valor float da pilha e empilha no frame chamador
 * @param void
 * @return void
 */
void freturn()
{
	retorno = pop_op();
	flagRet = 1;

	frameCorrente->pc = frameCorrente->code_length + 1;
}

/**
 * @brief Retira dois valores(double) da pilha e empilha no frame chamador
 * @param void
 * @return void
 */
void dreturn()
{
	int32_t alta, baixa;

	baixa = pop_op();
	alta = pop_op();

	flagRet = 2;

	retAlta = alta;
	retBaixa = baixa;

	frameCorrente->pc = frameCorrente->code_length + 1;
}

/**
 * @brief Retira uma referencia da pilha e empilha na pilha do chamador
 * @param void
 * @return void
 */
void areturn()
{
	retorno = pop_op();
	flagRet = 1;

	frameCorrente->pc = frameCorrente->code_length + 1;
}

/**
 * @brief Empilha o valor 0 no frame chamador
 * @param void
 * @return void
 */
void ins_return()
{
	// setar variaveis globais de retorno para 0
	retorno = 0;
	flagRet = 0;

	atualizaPc();
}

/**
 * @brief
 * @param void
 * @return void
 */
void getstatic()
{
	// TODO
	frameCorrente->pilha_op->depth += 1;
	atualizaPc();
}

/**
 * @brief
 * @param void
 * @return void
 */
void putstatic()
{
	// TODO
}

/**
 * @brief Funcao acessa um field do objeto e empilha na pilha de operandos do
 * frame corrente.
 * @param void
 * @return void
 */
void getfield()
{
	// Pega indice no argumento da instrucao
	uint32_t indice = frameCorrente->code[frameCorrente->pc + 2];

	// Acessa o indice da classe que possui o field.
	int32_t indiceClasse = frameCorrente->constant_pool[indice - 1].info.Fieldref.class_index;

	// Obtem o nome da classe a partir do indice obtido anteriormente
	char *nomeClasse = retornaNome(frameCorrente->classe, frameCorrente->constant_pool[indiceClasse - 1].info.Class.name_index);

	// Obtem agora o indice do nome e do tipo
	uint16_t nomeTipoIndice = frameCorrente->constant_pool[indice - 1].info.Fieldref.name_and_type_index;

	// Obtem finalmente o nome e o tipo do field
	char *nome = retornaNome(frameCorrente->classe, frameCorrente->constant_pool[nomeTipoIndice - 1].info.NameAndType.name_index);
	char *tipo = retornaNome(frameCorrente->classe, frameCorrente->constant_pool[nomeTipoIndice - 1].info.NameAndType.descriptor_index);
	tipoGlobal = tipo;

	if ((strcmp(tipo, "Ljava/util/Scanner;") == 0))
	{
		atualizaPc();
		return;
	}

	objeto *obj = (objeto *)pop_op();

	// Obtem indice do field utilizando as informacões anteriores
	int32_t indiceField = buscaCampo(nomeClasse, nome, tipo);

	// obtem indice do nome do field (variavel)
	uint32_t indiceNome = frameCorrente->classe->fields[indiceField].name_index;

	if (tipo[0] == 'J' || tipo[0] == 'D')
	{
		int32_t i;
		for (i = 0; obj->indiceCampos[i] != indiceNome; i++)
			;

		int32_t baixa = obj->campos[i];
		int32_t alta = obj->campos[i + 1];

		push(alta);
		push(baixa);
		atualizaPc();
	}
	else
	{

		int32_t i;
		for (i = 0; obj->indiceCampos[i] != indiceNome; i++)
			;
		// Pega o field do objeto e empilha
		uint32_t val = obj->campos[i];

		push(val);

		atualizaPc();
	}
}

/**
 * @brief Funcao que acessa valor na pilha e atribui ao objeto que o executa
 * @param void
 * @return void
 */
void putfield()
{
	// Pega indice no argumento da instrucao
	uint32_t indice = frameCorrente->code[frameCorrente->pc + 2];

	// Acessa o indice da classe que possui o field.
	int32_t indiceClasse = frameCorrente->constant_pool[indice - 1].info.Fieldref.class_index;

	// Obtem o nome da classe a partir do indice obtido anteriormente
	char *nomeClasse = retornaNome(frameCorrente->classe, frameCorrente->constant_pool[indiceClasse - 1].info.Class.name_index);

	// Obtem agora o indice do nome e do tipo
	uint16_t nomeTipoIndice = frameCorrente->constant_pool[indice - 1].info.Fieldref.name_and_type_index;

	// Obtem finalmente o nome e o tipo do field
	char *nome = retornaNome(frameCorrente->classe, frameCorrente->constant_pool[nomeTipoIndice - 1].info.NameAndType.name_index);
	char *tipo = retornaNome(frameCorrente->classe, frameCorrente->constant_pool[nomeTipoIndice - 1].info.NameAndType.descriptor_index);

	// Obtem indice do field utilizando as informacões anteriores
	int32_t indiceField = buscaCampo(nomeClasse, nome, tipo);

	// obtem indice do nome do field (variavel)
	uint32_t indiceNome = frameCorrente->classe->fields[indiceField].name_index;

	// obtem valor e objeto da pilha e seta o valor no field do objeto
	if (tipo[0] == 'J' || tipo[0] == 'D')
	{
		int32_t alta, baixa;
		int32_t val1 = pop_op();
		int32_t val2 = pop_op();
		objeto *obj = (objeto *)pop_op();

		// Converter os numeros 32 bits para 64 bits(double)

		int64_t dVal = val2; // Atribui parte alta primeiro
		dVal <<= 32;				 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
		dVal = dVal + val1;	 // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

		double valorDouble1; // Copia os bytes do int64_t para um double (memcpy copia 64 bits de dVal para valorDouble1)
		memcpy(&valorDouble1, &dVal, sizeof(int64_t));

		int i;
		for (i = 0; obj->indiceCampos[i] != indiceNome; i++)
			;

		int64_t valorPilha; // Converte mais uma vez o double somado para int64 para empilhar corretamente
		memcpy(&valorPilha, &valorDouble1, sizeof(int64_t));

		// Converte para parte alta e baixa novamente para empilhar
		alta = valorPilha >> 32;
		baixa = valorPilha & 0xffffffff;
		obj->campos[i] = baixa;
		obj->campos[i + 1] = alta;
	}
	else
	{
		int32_t val = pop_op();
		objeto *obj = (objeto *)pop_op();
		int i;
		for (i = 0; obj->indiceCampos[i] != indiceNome; i++)
			;
		obj->campos[i] = val;
	}

	atualizaPc();
}

/**
 * @brief Funcao que invoca metodos de uma classe que nao se enquadram nas demais
 * categorias (static,interface,special)
 * @param void
 * @return void
 */
void invokevirtual()
{
	method_info *metodoInvocado;
	char *nomeClasse;
	char *nomeMetodo;
	char *descricaoMetodo;
	uint16_t nomeMetodoAux, descricaoMetodoAux, nomeTipoAux, stringAux;
	int32_t resultado, resultado2, resultado_string;
	int32_t classeIndice;
	uint8_t *string = NULL;
	static int8_t flagAppend = 0;

	uint32_t pcAux = frameCorrente->code[frameCorrente->pc + 2];

	classeIndice = frameCorrente->constant_pool[pcAux - 1].info.Methodref.class_index;

	nomeClasse = retornaNome(frameCorrente->classe, frameCorrente->constant_pool[classeIndice - 1].info.Class.name_index);
	nomeTipoAux = frameCorrente->constant_pool[pcAux - 1].info.Methodref.name_and_type_index;

	nomeMetodoAux = frameCorrente->constant_pool[nomeTipoAux - 1].info.NameAndType.name_index;

	descricaoMetodoAux = frameCorrente->constant_pool[nomeTipoAux - 1].info.NameAndType.descriptor_index;

	nomeMetodo = retornaNome(frameCorrente->classe, nomeMetodoAux);

	descricaoMetodo = retornaNome(frameCorrente->classe, descricaoMetodoAux);

	if ((strcmp(nomeClasse, "java/lang/StringBuffer") == 0) && (strcmp(nomeMetodo, "append") == 0))
	{
		flagAppend++;
		foi_lneg = false;
		atualizaPc();
		return;
	}

	if ((strcmp(nomeClasse, "java/lang/StringBuffer") == 0) && (strcmp(nomeMetodo, "toString") == 0))
	{
		foi_lneg = false;
		atualizaPc();
		return;
	}

	if ((strcmp(nomeClasse, "java/util/Scanner") == 0) && (strcmp(nomeMetodo, "next") == 0))
	{
		int32_t aux;
		scanf("%d", &aux);
		push(aux);
		foi_lneg = false;
		atualizaPc();
		return;
	}

	if ((strcmp(nomeClasse, "java/io/PrintStream") == 0) && (strcmp(nomeMetodo, "println") == 0))
	{
		if (strcmp(descricaoMetodo, "()V") == 0)
		{
			printf("\n");
		}

		else if (flagAppend == 0)
		{
			resultado = pop_op();
			if (tipoGlobal == NULL)
			{
				string = frameCorrente->constant_pool[resultado].info.Utf8.bytes;
			}

			if (string != NULL)
			{
				printf("%s\n", string);
			}
			else if (strcmp(tipoGlobal, "Z") == 0)
			{
				if (resultado)
				{
					printf("TRUE\n");
				}
				else
				{
					printf("FALSE\n");
				}
			}
			else if (strcmp(tipoGlobal, "F") == 0)
			{
				float valDesemp;
				memcpy(&valDesemp, &resultado, sizeof(float));
				printf("%f\n", valDesemp);
			}

			else if (strcmp(tipoGlobal, "D") == 0)
			{
				resultado2 = pop_op();
				double resultado_double;
				int64_t temp;

				temp = resultado2;
				temp <<= 32;
				temp += resultado;
				memcpy(&resultado_double, &temp, sizeof(int64_t));
				printf("%f\n", resultado_double);
			}

			else if (strcmp(tipoGlobal, "L") == 0)
			{
				resultado2 = pop_op();
				int64_t long_num;
				long long result;

				long_num = resultado2;
				long_num <<= 32;
				long_num |= resultado;

				memcpy(&result, &long_num, sizeof(long));
				foi_lneg = false;
				if (!foi_lneg)
				{
					printf("%" PRId64 "\n", long_num);
				}
				else
				{
					printf("%" PRId64 "\n", result);
				}
			}

			else if (strcmp(tipoGlobal, "I") == 0)
			{
				printf("%d\n", resultado);
			}

			else if (strcmp(tipoGlobal, "C") == 0)
			{
				printf("%c\n", resultado);
			}

			else
			{
				printf("erro no invoke_virtual, tipoGlobal ainda nao setado");
				exit(1);
			}
		}

		else if (flagAppend == 2)
		{
			if (strcmp(tipoGlobal, "F") == 0)
			{
				resultado = pop_op();
				resultado_string = pop_op();

				string = frameCorrente->constant_pool[resultado_string].info.Utf8.bytes;
				if (string != NULL)
				{
					printf("%s", string);
				}

				float valDesemp;
				memcpy(&valDesemp, &resultado, sizeof(float));
				printf("%f\n", valDesemp);
			}

			else if (strcmp(tipoGlobal, "I") == 0)
			{
				resultado = pop_op();
				resultado_string = pop_op();

				string = frameCorrente->constant_pool[resultado_string].info.Utf8.bytes;
				if (string != NULL)
				{
					printf("%s", string);
				}
				printf("%d\n", resultado);
			}

			else if (strcmp(tipoGlobal, "D") == 0)
			{
				resultado = pop_op();
				resultado2 = pop_op();
				resultado_string = pop_op();

				double resultado_double;
				int64_t temp;

				temp = resultado2;
				temp <<= 32;
				temp += resultado;

				if (string != NULL)
				{
					printf("%s", string);
				}

				memcpy(&resultado_double, &temp, sizeof(int64_t));
				printf("%lf\n", resultado_double);
			}

			else
			{
				printf("tipoGlobal ainda nao reconhecido");
				exit(1);
			}

			flagAppend = 0;
		}
		else
		{
			return;
		}

		foi_lneg = false;
		atualizaPc();
		return;
	}

	classeIndice = carregaMemClasse(nomeClasse);
	classFile *classe = buscaClasseIndice(classeIndice);

	// Busca metodo a ser invocado
	metodoInvocado = buscaMetodo(frameCorrente->classe, classe, nomeTipoAux);
	if (metodoInvocado == NULL)
	{
		printf("Metodo nao Encontrado!\n");
		exit(0);
	}

	int32_t numeroParametros = retornaNumeroParametros(classe, metodoInvocado); // Pega parametros da pilha pelo numero de fields
	uint32_t *fields = calloc(sizeof(uint32_t), numeroParametros + 1);					// Aloca espaco para os parametros do metodo

	// Desempilha os parametros da pilha
	for (int32_t i = 0; i <= numeroParametros; i++)
	{
		fields[i] = pop_op();
	}

	empilhaMetodo(metodoInvocado, classe); // Inicia metodo

	// Preenche fields no frame novo (invoke)
	for (int32_t i = 0; i <= numeroParametros; i++)
	{
		frameCorrente->fields[i] = fields[numeroParametros - i];
	}

	executaFrameCorrente(); // Executa metodo

	foi_lneg = false;
	atualizaPc();
	return;
}

/**
 * @brief Funcao que invoca metodos especiais de uma classe
 * @param void
 * @return void
 */
void invokespecial()
{
	method_info *metodoInvocado;
	// Executar instrucao

	uint32_t indice = frameCorrente->code[frameCorrente->pc + 2];																																	 // Pega indice no argumento da instrucao
	uint32_t indiceClasse = (frameCorrente->constant_pool[indice - 1]).info.Methodref.class_index;																 // Pega o indice do nome da classe na CP pelo indice anterior
	char *nomeClasse = retornaNome(frameCorrente->classe, (frameCorrente->constant_pool[indiceClasse - 1]).info.Class.name_index); // Pega nome da classe

	if (strcmp("java/lang/Object", nomeClasse) == 0)
	{
		carregaMemClasse(nomeClasse);
		atualizaPc();
		return;
	}

	if (strcmp("java/lang/StringBuffer", nomeClasse) == 0)
	{
		atualizaPc();
		return;
	}

	if (strcmp("java/util/Scanner", nomeClasse) == 0)
	{
		atualizaPc();
		return;
	}

	int32_t indexClasse = carregaMemClasse(nomeClasse);																										 // Pega posicao da classe no array de classes
	classFile *classe = buscaClasseIndice(indexClasse);																										 // Pega referencia ao classFile pelo indice anterior
	uint16_t nomeTipoIndice = frameCorrente->constant_pool[indice - 1].info.Methodref.name_and_type_index; // Pega o nome e tipo do metodo pelo indice da instrucao
	metodoInvocado = buscaMetodo(frameCorrente->classe, classe, nomeTipoIndice);													 // Busca metodo a ser invocado
	int32_t numeroParametros = retornaNumeroParametros(classe, metodoInvocado);														 // Pega parametros da pilha pelo numero de fields
	uint32_t *fields = calloc(sizeof(uint32_t), numeroParametros + 1);																		 // Aloca espaco para os parametros do metodo

	// Desempilha os parametros da pilha
	for (int32_t i = 0; i <= numeroParametros; i++)
	{
		fields[i] = pop_op();
	}

	empilhaMetodo(metodoInvocado, classe); // Inicia metodo

	// Preenche fields no frame novo (invoke)
	for (int32_t i = 0; i <= numeroParametros; i++)
	{
		frameCorrente->fields[i] = fields[numeroParametros - i];
	}

	executaFrameCorrente(); // Executa metodo

	atualizaPc();
}

/**
 * @brief Funcao que invoca metodos estaticos de uma classe
 * @param void
 * @return void
 */
void invokestatic()
{
	method_info *metodoInvocado;

	char *nomeMetodo;
	char *descricaoMetodo;
	uint16_t nomeMetodoAux, descricaoMetodoAux, nomeTipoAux, stringAux;

	uint32_t indice = frameCorrente->code[frameCorrente->pc + 2];																																	 // Pega indice no argumento da instrucao
	uint32_t indiceClasse = (frameCorrente->constant_pool[indice - 1]).info.Methodref.class_index;																 // Pega o indice do nome da classe na CP pelo indice anterior
	char *nomeClasse = retornaNome(frameCorrente->classe, (frameCorrente->constant_pool[indiceClasse - 1]).info.Class.name_index); // Pega nome da classe

	nomeTipoAux = frameCorrente->constant_pool[indice - 1].info.Methodref.name_and_type_index;
	nomeMetodoAux = frameCorrente->constant_pool[nomeTipoAux - 1].info.NameAndType.name_index;
	descricaoMetodoAux = frameCorrente->constant_pool[nomeTipoAux - 1].info.NameAndType.descriptor_index;
	nomeMetodo = retornaNome(frameCorrente->classe, nomeMetodoAux);
	descricaoMetodo = retornaNome(frameCorrente->classe, descricaoMetodoAux);

	if ((strcmp(nomeClasse, "java/lang/System") == 0) && (strcmp(nomeMetodo, "exit") == 0))
	{
		if (strstr(descricaoMetodo, "(I)V") != NULL)
		{
			int32_t retPilha = pop_op();
			exit(retPilha);
			atualizaPc();
			return;
		}
	}

	if ((strcmp(nomeClasse, "java/lang/Integer") == 0) && (strcmp(nomeMetodo, "parseInt") == 0))
	{

		int32_t retPilha = pop_op();
		pop_op();
		push(retPilha);
		atualizaPc();
		return;
	}

	if ((strcmp(nomeClasse, "java/lang/Math") == 0) && (strcmp(nomeMetodo, "sqrt") == 0))
	{
		if (strstr(descricaoMetodo, "(D)D") != NULL)
		{
			int32_t baixa = pop_op();
			int32_t alta = pop_op();

			int64_t dVal = alta; // Atribui parte alta primeiro
			dVal <<= 32;				 // Shifta 32 pra esquerda abrindo espaco para a parte baixa a direita
			dVal = dVal + baixa; // Preenche os 32 bits inferiores com a parte baixa (Basta somar pois os 32 bits da parte baixa estao zerados)

			double valorDouble1; // Copia os bytes do int64_t para um double (memcpy copia 64 bits de dVal para valorDouble1)
			memcpy(&valorDouble1, &dVal, sizeof(int64_t));

			valorDouble1 = sqrt(valorDouble1); // Tira raiz

			int64_t aux; // Volta para 64 bits para empilhar
			memcpy(&aux, &valorDouble1, sizeof(int64_t));

			alta = aux >> 32; // Converte para parte alta e baixa novamente para empilhar
			baixa = aux & 0xffffffff;

			push(alta);
			push(baixa);

			atualizaPc();
			return;
		}
	}

	int32_t indexClasse = carregaMemClasse(nomeClasse);																										 // Pega posicao da classe no array de classes
	classFile *classe = buscaClasseIndice(indexClasse);																										 // Pega referencia ao classFile pelo indice anterior
	uint16_t nomeTipoIndice = frameCorrente->constant_pool[indice - 1].info.Methodref.name_and_type_index; // Pega o nome e tipo do metodo pelo indice da instrucao
	metodoInvocado = buscaMetodo(frameCorrente->classe, classe, nomeTipoIndice);													 // Busca metodo a ser invocado
	int32_t numeroParametros = retornaNumeroParametros(classe, metodoInvocado);														 // Pega parametros da pilha pelo numero de fields
	uint32_t *fields = calloc(sizeof(uint32_t), numeroParametros + 1);																		 // Aloca espaco para os parametros do metodo

	// Desempilha os parametros da pilha
	for (int32_t i = 0; i < numeroParametros; i++)
		fields[i] = pop_op();

	empilhaMetodo(metodoInvocado, classe); // Inicia metodo

	// Preenche fields no frame novo (invoke)
	for (int32_t i = 0; i < numeroParametros; i++)
	{
		frameCorrente->fields[i] = fields[numeroParametros - i - 1];
	}

	executaFrameCorrente(); // Executa metodo
	atualizaPc();
}

/**
 * @brief Funcao que invoca metodos implementados de uma interface
 * @param void
 * @return void
 */
void invokeinterface()
{
	method_info *metodoInvocado;

	char *nomeMetodo;
	char *descricaoMetodo;
	uint16_t nomeMetodoAux, descricaoMetodoAux, nomeTipoAux, stringAux;

	uint32_t indice = frameCorrente->code[frameCorrente->pc + 2];																																	 // Pega indice no argumento da instrucao
	uint32_t indiceClasse = (frameCorrente->constant_pool[indice - 1]).info.Methodref.class_index;																 // Pega o indice do nome da classe na CP pelo indice anterior
	char *nomeClasse = retornaNome(frameCorrente->classe, (frameCorrente->constant_pool[indiceClasse - 1]).info.Class.name_index); // Pega nome da classe
	nomeTipoAux = frameCorrente->constant_pool[indice - 1].info.Methodref.name_and_type_index;
	nomeMetodoAux = frameCorrente->constant_pool[nomeTipoAux - 1].info.NameAndType.name_index;
	descricaoMetodoAux = frameCorrente->constant_pool[nomeTipoAux - 1].info.NameAndType.descriptor_index;
	nomeMetodo = retornaNome(frameCorrente->classe, nomeMetodoAux);
	descricaoMetodo = retornaNome(frameCorrente->classe, descricaoMetodoAux);

	int32_t indexClasse = carregaMemClasse(nomeClasse);																										 // Pega posicao da classe no array de classes
	classFile *classe = buscaClasseIndice(indexClasse);																										 // Pega referencia ao classFile pelo indice anterior
	uint16_t nomeTipoIndice = frameCorrente->constant_pool[indice - 1].info.Methodref.name_and_type_index; // Pega o nome e tipo do metodo pelo indice da instrucao
	metodoInvocado = buscaMetodo(frameCorrente->classe, classe, nomeTipoIndice);													 // Busca metodo a ser invocado
	int32_t numeroParametros = retornaNumeroParametros(classe, metodoInvocado);														 // Pega parametros da pilha pelo numero de fields
	uint32_t *fields = calloc(sizeof(uint32_t), numeroParametros + 1);																		 // Aloca espaco para os parametros do metodo

	// Desempilha os parametros da pilha
	for (int32_t i = 0; i < numeroParametros; i++)
		fields[i] = pop_op();

	empilhaMetodo(metodoInvocado, classe); // Inicia metodo

	// Preenche fields no frame novo (invoke)
	for (int32_t i = 0; i < numeroParametros; i++)
	{
		frameCorrente->fields[i] = fields[numeroParametros - i - 1];
	}

	executaFrameCorrente(); // Executa metodo
	atualizaPc();
}

/**
 * @brief Funcao que cria um objeto (struct objeto) e adiciona no heap(array)
 * @param void
 * @return void
 */
void ins_new()
{
	uint32_t indice;
	int32_t aux;
	char *nomeClasse;
	classFile *classe;
	objeto *objeto;
	// TODO cria objeto no heap (array)

	indice = frameCorrente->code[2 + (frameCorrente->pc)];																													 // Pega indice na instrucao
	nomeClasse = retornaNome(frameCorrente->classe, frameCorrente->constant_pool[indice - 1].info.Class.name_index); // Pega o nome da classe apontado pelo indice

	if (strcmp("java/util/Scanner", nomeClasse) == 0)
	{
		naoEmpilhaFlag = 1;
		atualizaPc();
		return;
	}

	if (strcmp("java/lang/StringBuffer", nomeClasse) == 0)
	{
		naoEmpilhaFlag = 1;
		atualizaPc();
		return;
	}

	aux = carregaMemClasse(nomeClasse); // Busca indice da classe no array de classeFiles
	classe = buscaClasseIndice(aux);		// Pega classFile pelo indice no array de classes
	objeto = criaObjeto(classe);				// Cria um objeto a partir do classFile

	if (objeto == NULL)
	{
		printf("Objeto nao foi corretamente alocado\n");
	}

	push((int32_t)objeto); // empilha objeto na pilha de operandos (push)
	atualizaPc();
}

/**
 * @brief Aloca um array simples e empilha uma referencia pra esse array
 * Desempilha o tamanho do array. Obtem tipo do array da instrucao
 * @param void
 * @return void
 */
void newarray()
{
	int32_t tamanhoBytes;																						 // Descreve o tamanho em bytes de cada tipo. int -> 4 bytes por exemplo
	int32_t tamanhoArray = pop_op();																 // Pega da pilha o tamanho do array
	int8_t tipoArray = frameCorrente->code[(frameCorrente->pc) + 1]; // Pega da instrucao o tipo do array

	// Necessario descobrir tipo para alocar a quantidade certa
	// Atraves do tamanho em bits de cada tipo

	// Long
	if (tipoArray == 11)
	{
		tamanhoBytes = 8;
	}
	// Double
	if (tipoArray == 7)
	{
		tamanhoBytes = 8;
	}
	// Float
	if (tipoArray == 6)
	{
		tamanhoBytes = 4;
	}
	// Referencia
	if (tipoArray == 0)
	{
		tamanhoBytes = 4;
	}
	// Int
	if (tipoArray == 10)
	{
		tamanhoBytes = 4;
	}
	// Char
	if (tipoArray == 5)
	{
		tamanhoBytes = 2;
	}
	// Short
	if (tipoArray == 9)
	{
		tamanhoBytes = 2;
	}
	// Booleano
	if (tipoArray == 4)
	{
		tamanhoBytes = 1;
	}
	// Byte
	if (tipoArray == 8)
	{
		tamanhoBytes = 1;
	}

	// Array como ponteiro pra void -> realiza cast futuramente
	// Aloca espaco de acordo com os tamanhos
	int32_t *vetor = calloc(tamanhoBytes, tamanhoArray);

	// Necessario guardar as struct para o arrayLength
	// e feito um vetor de arrays para obter o tamanho dos arrays
	qtdArrays++;
	arrayVetores = realloc(arrayVetores, sizeof(struct array) * qtdArrays);
	arrayVetores[qtdArrays - 1].tamanho = tamanhoArray;
	arrayVetores[qtdArrays - 1].referencia = (int32_t)vetor;
	arrayVetores[qtdArrays - 1].tipo = tipoArray;

	push((int32_t)vetor); // Empilha referencia pro vetor
	atualizaPc();					// Atualiza pc
}

/**
 * @brief Aloca um array de objetos e empilha uma referencia pra esse array
 * Desempilha o tamanho do array
 * @param void
 * @return void
 */
void anewarray()
{
	int32_t tamanhoBytes;																						 // Descreve o tamanho em bytes de cada tipo. int -> 4 bytes por exemplo
	int32_t tamanhoArray = pop_op();																 // Pega da pilha o tamanho do array
	int8_t tipoArray = frameCorrente->code[(frameCorrente->pc) + 1]; // Pega da instrucao o tipo do array

	// Necessario descobrir tipo para alocar a quantidade certa
	// Atraves do tamanho em bits de cada tipo

	// Long
	if (tipoArray == 11)
	{
		tamanhoBytes = 8;
	}
	// Double
	if (tipoArray == 7)
	{
		tamanhoBytes = 8;
	}
	// Float
	if (tipoArray == 6)
	{
		tamanhoBytes = 4;
	}
	// Referencia
	if (tipoArray == 0)
	{
		tamanhoBytes = 4;
	}
	// Int
	if (tipoArray == 10)
	{
		tamanhoBytes = 4;
	}
	// Char
	if (tipoArray == 5)
	{
		tamanhoBytes = 2;
	}
	// Short
	if (tipoArray == 9)
	{
		tamanhoBytes = 2;
	}
	// Booleano
	if (tipoArray == 4)
	{
		tamanhoBytes = 1;
	}
	// Byte
	if (tipoArray == 8)
	{
		tamanhoBytes = 1;
	}

	// Array como ponteiro pra void -> realiza cast futuramente
	// Aloca espaco de acordo com os tamanhos
	int32_t *vetor = calloc(tamanhoBytes, tamanhoArray);

	// Necessario guardar as struct para o arrayLength
	// e feito um vetor de arrays para obter o tamanho dos arrays
	qtdArrays++;
	arrayVetores = realloc(arrayVetores, sizeof(struct array) * qtdArrays);
	arrayVetores[qtdArrays - 1].tamanho = tamanhoArray;
	arrayVetores[qtdArrays - 1].referencia = (int32_t)vetor;
	arrayVetores[qtdArrays - 1].tipo = tipoArray;

	push((int32_t)vetor); // Empilha referencia pro vetor
	atualizaPc();					// Atualiza pc
}

/**
 * @brief Funcao que obtem uma referencia a um array alocado e
 * acessa sua struct para empilhar o tamanho (length) do array
 * @param void
 * @return void
 */
void arraylength()
{
	int32_t arrayRef = pop_op(); // Obtem referencia ao array alocado no newarray
	int i = 0;
	// Percore a quantidade de arrays alocados em busca do array correto
	while (i < qtdArrays)
	{
		// percorre o array de vetores em busca da referencia desempilhada
		if (arrayVetores[i].referencia == arrayRef)
		{
			int32_t length = arrayVetores[i].tamanho;
			push(length); // Empilha o length do array
			atualizaPc();
			return;
		}
		i++;
	}
	// Nao encontrou o array no vetor de arrays
	push(0);
	atualizaPc();
}

/**
 * @brief Funcao que checa se o objeto retirado da pilha de operandos
 * e do tipo fornecido por um indice pra constant pool
 * OBS: Parecida com a instanceof porem trata o null diferente
 * e o valor empilhado no final
 * @param void
 * @return void
 */
void checkcast()
{
	int16_t indice;
	int8_t offset1, offset2;

	// Pega os offsets da instrucao para acesso a constant pool
	offset1 = frameCorrente->code[(frameCorrente->pc) + 1];
	offset2 = frameCorrente->code[(frameCorrente->pc) + 2];

	indice = (offset1 << 8) | offset2; // Concatena para formar indice de 16 bits

	objeto *objeto = (struct objeto *)pop_op(); // Obtem referencia do objeto da pilha de operandos

	// De acordo com a especificacao se for nulo a pilha nao se altera
	if (objeto == NULL)
	{
		printf("Objeto nulo!\n");
	}

	char *nomeClasse = retornaNomeClasse(objeto->classe);					 // Pega tipo da classe desempilhada
	char *nomeIndice = retornaNome(frameCorrente->classe, indice); // Pega na constant pool tipo fornecido pelo indice

	// Se for igual
	if (strcmp(nomeClasse, nomeIndice) == 0)
	{
		printf("Objeto e do tipo: %s\n", nomeIndice);
	}

	// Empilha referencia de volta
	push((int32_t)objeto);
	atualizaPc();
}

/**
 * @brief Funcao que checa se o objeto retirado da pilha de operandos
 * e do tipo fornecido por um indice pra constant pool
 * OBS: Parecida com a checkcast porem trata o null diferente
 * e o valor empilhado no final
 * @param void
 * @return void
 */
void instanceof ()
{
	int16_t indice;
	int8_t offset1, offset2;

	// Pega os offsets da instrucao para acesso a constant pool
	offset1 = frameCorrente->code[(frameCorrente->pc) + 1];
	offset2 = frameCorrente->code[(frameCorrente->pc) + 2];

	indice = (offset1 << 8) | offset2;					// Concatena para formar indice de 16 bits
	objeto *objeto = (struct objeto *)pop_op(); // Obtem referencia do objeto da pilha de operandos

	// De acordo com a especificacao se for nulo empilha o valor 0
	if (objeto == NULL)
	{
		printf("Objeto nulo!\n");
		push(0);
	}

	char *nomeClasse = retornaNomeClasse(objeto->classe);					 // Pega tipo da classe desempilhada
	char *nomeIndice = retornaNome(frameCorrente->classe, indice); // Pega na constant pool tipo fornecido pelo indice

	// Se for igual empilha 1.
	if (strcmp(nomeClasse, nomeIndice) == 0)
	{
		printf("Objeto e do tipo: %s\n", nomeIndice);
		push(1);
	}
	atualizaPc();
}

/**
 * @brief
 */
void wide()
{
}

/**
 * @brief
 */
void multianewarray()
{
}

/**
 * @brief Funcao que pega dois bytes da instrucao se operando for null realiza jump
 * @param void
 * @return void
 */
void ifnull()
{
	uint8_t offset1, offset2;
	int16_t offset;

	// Pega offset para salto
	offset1 = frameCorrente->code[frameCorrente->pc + 1];
	offset2 = frameCorrente->code[frameCorrente->pc + 2];
	offset = offset1;
	offset <<= 8;
	offset |= offset2;

	int32_t retPilha = pop_op(); // Pega valor a ser comparado na pilha

	// Se val igual a null atualiza pc com offset se nao soma 3 para ir para proxima instrucao
	if (retPilha == 0)
	{
		frameCorrente->pc += offset;
	}
	else
	{
		frameCorrente->pc += 3;
	}
}

/**
 * @brief Funcao que pega dois bytes da instrucao se operando for diferente de null realiza jump
 * @param void
 * @return void
 */
void ifnonnull()
{
	uint8_t offset1, offset2;
	int16_t offset;

	// Pega offset para salto
	offset1 = frameCorrente->code[frameCorrente->pc + 1];
	offset2 = frameCorrente->code[frameCorrente->pc + 2];
	offset = offset1;
	offset <<= 8;
	offset |= offset2;

	int32_t retPilha = pop_op(); // Pega valor a ser comparado na pilha

	// Se val igual a null atualiza pc com offset se nao soma 3 para ir para proxima instrucao
	if (retPilha != 0)
	{
		frameCorrente->pc += offset;
	}
	else
	{
		frameCorrente->pc += 3;
	}
}

/**
 * @brief Funcao que realiza um jump a partir de um offset(wide) da instrucao
 * @param void
 * @return void
 */
void goto_w()
{
	int32_t deslocamento, offset1, offset2, offset3, offset4;

	// Pega os offsets
	offset1 = frameCorrente->code[frameCorrente->pc + 1];
	offset2 = frameCorrente->code[frameCorrente->pc + 2];
	offset3 = frameCorrente->code[frameCorrente->pc + 3];
	offset4 = frameCorrente->code[frameCorrente->pc + 4];

	// Concatena para gerar o deslocamento.
	deslocamento = (offset1 & 0xFF) << 24;
	deslocamento |= (offset2 & 0xFF) << 16;
	deslocamento |= (offset3 & 0xFF) << 8;
	deslocamento |= (offset4 & 0xFF);

	frameCorrente->pc += deslocamento;
}

/**
 * @brief Jump SubRoutine. Pula para regiao formada por 4 offsets
 * salva na pilha endereco de retorno da proxima instrucao
 * @param void
 * @return void
 */
void jsr_w()
{
	int32_t deslocamento, offset1, offset2, offset3, offset4;

	push(frameCorrente->code[frameCorrente->pc + 5]); // Empilha valor de retorno para a proxima instrucao

	// Pega os offsets
	offset1 = frameCorrente->code[frameCorrente->pc + 1];
	offset2 = frameCorrente->code[frameCorrente->pc + 2];
	offset3 = frameCorrente->code[frameCorrente->pc + 3];
	offset4 = frameCorrente->code[frameCorrente->pc + 4];

	// Concatena para gerar o deslocamento.
	deslocamento = (offset1 & 0xFF) << 24;
	deslocamento |= (offset2 & 0xFF) << 16;
	deslocamento |= (offset3 & 0xFF) << 8;
	deslocamento |= (offset4 & 0xFF);

	frameCorrente->pc += deslocamento;
}
