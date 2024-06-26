/**
 * @file exibidor.c
 * @section DESCRIPTION
 * Universidade de Brasilia\n
 *
 * Leonardo Pereira Cortes - 200030582\n
 *
 * Software Basico - 2024.1\n
 * Professor: Marcelo Ladeira\n\n
 *
 * Arquivo que contem a funcao para imprimir no prompt a estrutura do classfile lida.
 */

#include "../includes/exibidor.h"

/**
 * @brief Imprime no prompt toda a estrutura de um classFile carregado no array de classes
 * @param cf Referencia para um classFile que representa um .class carregado no array de classes
 * @return void
 */
void imprimePrompt(classFile *cf)
{
	printf("----General Information----\n");
	printf("CAFEBABE: 0x%0x \n", cf->magic);
	printf("Minor version: %d \n", cf->minor_version);
	printf("Major version: %d \n", cf->major_version);
	printf("Constant Pool Count: %d \n", cf->constant_pool_count);
	printf("----End General----\n\n");

	printf("----Constant Pool----\n"); // imprime a constant pool

	// Itera pela constante pool para mostrar informacao
	for (int i = 0; i < cf->constant_pool_count - 1; i++)
	{
		int tag = cf->constant_pool[i].tag; // pega tag

		// De acordo com a tag atual, decide o que fazer
		switch (tag)
		{
		case CONSTANT_Class:
			printf("[%d] CONSTANT_Class_info - name_index: cp info #%d ", i + 1, cf->constant_pool[i].info.Class.name_index);
			imprime_string_pool(cf->constant_pool, cf->constant_pool[i].info.Class.name_index - 1);
			printf("\n");

			break;

		case CONSTANT_Fieldref:
			printf("[%d] CONSTANT_Fieldref_info - class_index: cp info #%d ", i + 1, cf->constant_pool[i].info.Fieldref.class_index);
			imprime_string_pool(cf->constant_pool, cf->constant_pool[i].info.Fieldref.class_index - 1);
			printf("\n");

			printf("[%d] CONSTANT_Fieldref_info - name_and_type_index: cp info #%d ", i + 1, cf->constant_pool[i].info.Fieldref.name_and_type_index);
			imprime_string_pool(cf->constant_pool, cf->constant_pool[i].info.Fieldref.name_and_type_index - 1);
			printf("\n");

			break;

		case CONSTANT_NameAndType:
			printf("[%d] CONSTANT_NameAndType_info - name_index: cp info info #%d ", i + 1, cf->constant_pool[i].info.NameAndType.name_index);
			imprime_string_pool(cf->constant_pool, cf->constant_pool[i].info.NameAndType.name_index - 1);
			printf("\n");

			printf("[%d] CONSTANT_NameAndType_info - descriptor_index: cp info #%d ", i + 1, cf->constant_pool[i].info.NameAndType.descriptor_index);
			imprime_string_pool(cf->constant_pool, cf->constant_pool[i].info.NameAndType.descriptor_index - 1);
			printf("\n");

			break;

		case CONSTANT_Utf8:
			printf("[%d] CONSTANT_Utf8_info - length:%d\n", i + 1, cf->constant_pool[i].info.Utf8.length);
			printf("[%d] CONSTANT_Utf8_info - bytes: %s\n", i + 1, cf->constant_pool[i].info.Utf8.bytes);
			break;

		case CONSTANT_Methodref:
			printf("[%d] CONSTANT_Methodref_info - class_index: cp info #%d ", i + 1, cf->constant_pool[i].info.Methodref.class_index);
			imprime_string_pool(cf->constant_pool, cf->constant_pool[i].info.Methodref.class_index - 1);
			printf("\n");

			printf("[%d] CONSTANT_Methodref_info - name_and_type_index: cp info #%d ", i + 1, cf->constant_pool[i].info.Methodref.name_and_type_index);
			imprime_string_pool(cf->constant_pool, cf->constant_pool[i].info.Methodref.name_and_type_index - 1);
			printf("\n");

			break;

		case CONSTANT_InterfaceMethodref:
			printf("[%d] CONSTANT_InterfaceMethodref_info - class_index: cp info #%d ", i + 1, cf->constant_pool[i].info.InterfaceMethodref.class_index);
			imprime_string_pool(cf->constant_pool, cf->constant_pool[i].info.Methodref.class_index - 1);
			printf("\n");

			printf("[%d] CONSTANT_InterfaceMethodref_info - name_and_type_index: cp info #%d ", i + 1, cf->constant_pool[i].info.InterfaceMethodref.name_and_type_index);
			imprime_string_pool(cf->constant_pool, cf->constant_pool[i].info.Methodref.name_and_type_index - 1);
			printf("\n");

			break;

		case CONSTANT_String:
			printf("[%d] CONSTANT_String_info - string_index: cp info #%d ", i + 1, cf->constant_pool[i].info.String.string_index);
			imprime_string_pool(cf->constant_pool, cf->constant_pool[i].info.String.string_index - 1);
			printf("\n");
			break;

		case CONSTANT_Integer:
			printf("[%d] CONSTANT_Integer_info - bytes:%d\n", i + 1, cf->constant_pool[i].info.Integer.bytes);
			break;

		case CONSTANT_Float:
			printf("[%d] CONSTANT_Float_info - bytes:%d\n", i + 1, cf->constant_pool[i].info.Float.bytes);
			float fVal1; // Converte para float e nao perde precisao
			memcpy(&fVal1, &cf->constant_pool[i].info.Float.bytes, sizeof(int32_t));
			printf("[%d] CONSTANT_Float_info - valor:%f\n", i + 1, fVal1);
			break;
		case CONSTANT_Double:
			printf("[%d] CONSTANT_Double_info - high-bytes: 0x%0x\n", i + 1, cf->constant_pool[i].info.Double.high_bytes);
			printf("[%d] CONSTANT_Double_info - low-bytes: 0x%0x\n", i + 1, cf->constant_pool[i].info.Double.low_bytes);

			int64_t dVal = cf->constant_pool[i].info.Double.high_bytes; // Atribui parte alta primeiro

			dVal <<= 32; // Shifta 32 pra esquerda abrindo espaço para a parte baixa a direita
			// Preenche os 32 bits inferiores com a parte baixa -> Basta somar pois os 32 bits da parte baixa estao zerados
			dVal = dVal + cf->constant_pool[i].info.Double.low_bytes;

			// Finalmente copia dos bytes do int64_t para um double - memcpy copia 64 bits de dVal para valorDouble1
			double valorDouble1;
			memcpy(&valorDouble1, &dVal, sizeof(int64_t));

			printf("[%d] CONSTANT_Double_info - valor: %f\n", i + 1, valorDouble1);
			break;
		default:
			break;
		}
	}
	printf("----End Pool----\n\n");

	printf("----Second General Info----\n");
	printf("Access Flags: 0x%0x ", cf->access_flags);
	printAF(cf->access_flags);
	printf("This Class: cp info #%d ", cf->this_class);
	imprime_string_pool(cf->constant_pool, cf->this_class - 1);
	printf("\n");
	printf("Super Class: cp info #%d ", cf->super_class);
	imprime_string_pool(cf->constant_pool, cf->super_class - 1);
	printf("\n");
	printf("interfaces_count: %d\n", cf->interfaces_count);
	if (cf->interfaces_count != 0)
	{
		printf("---- Interfaces ----\n");
		// le interface, pondo no array de interfaces
		for (int i = 0; i < cf->interfaces_count; i++)
		{
			printf("Interface: cp info #%d ", cf->interfaces[i]);
			imprime_string_pool(cf->constant_pool, cf->interfaces[i] - 1);
			printf("\n");
		}

		printf("---- End Interface ----\n");
	}
	printf("Fields Count: %d\n", cf->fields_count);
	if (cf->fields_count != 0)
	{
		printf("----Fields----\n");
		for (int i = 0; i < cf->fields_count; i++)
		{
			// imprime informacoes
			printf("Name: cp info #%d ", cf->fields[i].name_index);
			imprime_string_pool(cf->constant_pool, cf->fields[i].name_index - 1);
			printf("\n");
			printf("Descriptor: cp info #%d ", cf->fields[i].descriptor_index);
			imprime_string_pool(cf->constant_pool, cf->fields[i].descriptor_index - 1);
			printf("\n");
			printf("Access Flag: 0x%x ", cf->fields[i].access_flags);
			printAF(cf->fields[i].access_flags);

			for (int j = 0; j < cf->fields[i].attributes_count; j++)
			{
				printf("\t\t----Attribute Info do Field----\n");

				// imprime informacao dos atributos
				printf("attribute_name_index: cp info #%d\n", cf->fields[i].attributes->attribute_name_index);
				printf("attribute_length: %d\n", cf->fields[i].attributes->attribute_length);

				// imprime constant value index
				printf("constant_value_index: cp info #%d", cf->fields[i].attributes->constantvalue_index);
				imprime_string_pool(cf->constant_pool, cf->fields[i].descriptor_index - 1);
				printf("\n");

				printf("\t\t----Fim da Attribute Info do Field----\n");
			}
		}

		printf("----End Fields----\n");
	}

	imprime_methods(cf);

	printf("attributes_count: %d\n", cf->attributes_count);
	if (cf->attributes_count != 0)
	{
		attribute_info *cp = cf->attributes;
		for (uint16_t i = 0; i < cf->attributes_count; cp++)
		{
			printf("----Attributes Info----\n");
			printf("attribute_name_index: cp info #%d ", cp->attribute_name_index);
			imprime_string_pool(cf->constant_pool, cp->attribute_name_index - 1);
			printf("\n");
			printf("attribute_length: %d\n", cp->attribute_length);
			for (uint32_t j = 0; j < cp->attribute_length; cp->info++)
			{
				if (*(cp->info) != 0)
				{
					printf("Source file name index: cp info #%d ", *(cp->info));
					imprime_string_pool(cf->constant_pool, *(cp->info) - 1);
					printf("\n");
				}
				j++;
			}
			printf("----End Attributes----\n\n");
			i++;
		}
	}
	printf("----End Second General----\n\n");
}

/**
 * @brief Imprime no prompt a string correspondente ao access flag
 * @param access_flags valor do access flag
 * @return void
 */
void printAF(uint16_t access_flags)
{
	if (access_flags == 0x0000)
		printf("\n");
	if (access_flags == 0x0001 || access_flags == 0x0021)
		printf("Public\n");
	if (access_flags == 0x0009)
		printf("Public Static\n");
	if (access_flags == 0x0002)
		printf("Private\n");
	if (access_flags == 0x0004)
		printf("Protected\n");
	if (access_flags == 0x0008)
		printf("Static\n");
	if (access_flags == 0x0010)
		printf("Final\n");
	if (access_flags == 0x0020)
		printf("Super\n");
	if (access_flags == 0x0200)
		printf("Interface\n");
	if (access_flags == 0x0400)
		printf("Abstract\n");
}

/**
 * @brief Imprime no prompt a estrutura de metodos presente no classFile
 * @param Referencia para um classFile que representa um .class carregado no array de classes
 * @return void
 */
void imprime_methods(classFile *cf)
{
	uint16_t name_ind;
	uint32_t att_len;
	uint16_t methods_count = cf->methods_count;

	printf("Methods Count: %d\n", cf->methods_count);
	if (methods_count == 0)
		return;
	else
	{
		method_info *cp = cf->methods;
		for (int i = 0; i < methods_count; cp++)
		{
			printf("access_flag: 0x%0x ", cp->access_flags);
			printAF(cp->access_flags);
			printf("name_index: cp info #%d ", cp->name_index);
			imprime_string_pool(cf->constant_pool, cp->name_index - 1);
			printf("\n");
			printf("descriptor_index: cp info #%d ", cp->descriptor_index);
			imprime_string_pool(cf->constant_pool, cp->descriptor_index - 1);
			printf("\n");
			printf("attributes_count: %d\n", cp->attributes_count);

			imprime_code(cf, cp->cd_atrb); // imprime code

			if (cp->attributes_count == 2) // se o metodo tem dois atributos, eh pq um eh code e o outro exceptions
			{
				imprime_exc(cf, cp->exc_atrb);
			}

			i++;
		}
		printf("----End Method----\n\n");
	}
}

/**
 * @brief Imprime no prompt a estrutura de code presente nos methods_info de cada classFile
 * @param cf Referencia para um classFile que representa um .class carregado no array de classes
 * @param cd_atrb Referencia para uma estrutura de code que possui os bytecodes misc e etc
 * @return void
 */
void imprime_code(classFile *cf, code_attribute *cd_atrb)
{
	int opcode, pos_referencia;
	int bytes_preench, offsets;
	uint32_t default_v, low, high, npairs, temp;

	printf("\n----Code Info----\n");
	printf("attribute_name_index: cp info #%d ", cd_atrb->attribute_name_index);
	imprime_string_pool(cf->constant_pool, cd_atrb->attribute_name_index - 1);
	printf("\n");
	printf("attribute_length: %d\n", cd_atrb->attribute_length);

	// imprime informacoes do stack
	printf("Tamanho maximo do Stack: %d\n", cd_atrb->max_stack);
	printf("Numero maximo de variaveis locais: %d\n", cd_atrb->max_locals);
	printf("Tamanho do codigo: %d\n", cd_atrb->code_length);

	// obtem decodificador de instrucoes
	decodificador dec[NUM_INSTRUCAO];
	inicializa_decodificador(dec);

	// k é incrementado conforme passa no loop
	for (uint32_t k = 0; k < cd_atrb->code_length;)
	{
		opcode = cd_atrb->code[k]; // pega opcode da instrucao
		printf("%d: %s  ", k, dec[opcode].instrucao);

		// toda vez que lemos bytes devemos incrementar k
		k++;

		if (opcode == TABLESWITCH)
		{
			// A posicao de referencia eh o label numerico associado a tableswitch (k-1 pois k ja foi incrementado para a proxima instrucao)
			pos_referencia = k - 1;

			// pega bytes de preenchimento - nao salva em nenhum lugar
			bytes_preench = (4 - (k % 4)) % 4;
			for (int l = 0; l < bytes_preench; l++)
			{
				k++;
			}

			// pega bytes do target default
			default_v = 0;
			for (int l = 0; l < 4; l++)
			{
				default_v = (default_v << 4) + cd_atrb->code[k];
				k++;
			}

			// pega bytes low
			low = 0;
			for (int l = 0; l < 4; l++)
			{
				low = (low << 4) + cd_atrb->code[k];
				k++;
			}

			// pega bytes high
			high = 0;
			for (int l = 0; l < 4; l++)
			{
				high = (high << 4) + cd_atrb->code[k];
				k++;
			}

			printf("  de  %d ateh %d\n", low, high);

			// pega bytes de offset
			offsets = 1 + high - low;
			for (int l = 0; l < offsets; l++)
			{
				// pega valor do offset atual
				temp = 0;
				for (int i = 0; i < 4; i++)
				{
					temp = (temp << 4) + cd_atrb->code[k];
					k++;
				}

				printf("\t%d: %d (+%d)\n", l, (pos_referencia + temp), temp);
			}
			printf("\tdefault: %d (+%d)\n", (default_v + pos_referencia), default_v);
		}

		else if (opcode == LOOKUPSWITCH)
		{
			// A posicao de referencia eh o label numerico associado a tableswitch (k-1 pois k ja foi incrementado para a proxima instrucao)
			pos_referencia = k - 1;

			// pega bytes de preenchimento
			bytes_preench = (4 - (k % 4)) % 4;
			for (int l = 0; l < bytes_preench; l++)
			{
				k++;
			}

			// pega bytes do target default
			default_v = 0;
			for (int l = 0; l < 4; l++)
			{
				default_v = (default_v << 4) + cd_atrb->code[k];
				k++;
			}

			// pega bytes low
			npairs = 0;
			for (int l = 0; l < 4; l++)
			{
				npairs = (npairs << 4) + cd_atrb->code[k];
				k++;
			}

			printf("  %d\n", npairs);

			// pega npairs
			for (uint32_t l = 0; l < npairs; l++)
			{
				// pega valor do match atual
				temp = 0;
				for (int i = 0; i < 4; i++)
				{
					temp = (temp << 8) + cd_atrb->code[k];
					k++;
				}
				printf("\t%d:  ", temp);

				// pega valor do offset
				temp = 0;
				for (int i = 0; i < 4; i++)
				{
					temp = (temp << 8) + cd_atrb->code[k];
					k++;
				}
				printf("%d (+%d)\n", temp + pos_referencia, temp);
			}
			printf("\tdefault: %d (+%d)\n", default_v + pos_referencia, default_v);
		}

		else if (opcode == WIDE)
		{
			printf("\n");

			// pega opcode que segue
			opcode = cd_atrb->code[k];
			k++;

			// se for um opcode do iload, fload, ...
			if (opcode == ILOAD || opcode == FLOAD || opcode == ALOAD || opcode == LLOAD ||
					opcode == DLOAD || opcode == ISTORE || opcode == FSTORE || opcode == ASTORE ||
					opcode == LSTORE || opcode == DSTORE || opcode == RET)
			{
				printf("%d: %s  ", k - 1, dec[opcode].instrucao);

				// pega index byte1
				k++;

				// pega index byte2
				k++;
				temp = cd_atrb->code[k - 2] << 8;
				temp += cd_atrb->code[k - 1];
				printf(" %u \n", temp);
			}

			// se for um iinc
			else if (opcode == IINC)
			{
				printf("%d: iinc ", k - 1);

				// pega indexbyte1
				k++;

				// pega indexbyte2
				k++;

				// adiciona o 1 pois comecamos a contar em 1
				temp = cd_atrb->code[k - 2] << 8;
				temp += cd_atrb->code[k - 1];
				printf(" %u ", temp);

				// pega constbyte1
				k++;

				// pega constbyte2
				k++;

				temp = cd_atrb->code[k - 2] << 8;
				temp += cd_atrb->code[k - 1];
				printf(" por  %u \n", temp);
			}
			else // senao
			{
				// Arquivo .class corrompido
				printf("Arquivo .class invalido na instrucao wide");
				exit(1);
			}
		}

		else
		{
			// obtem quantos operandos a instrucao tem e vai imprimindo operandos
			int num_bytes = dec[opcode].bytes;
			for (int l = 0; l < num_bytes; l++)
			{

				printf("%d  ", cd_atrb->code[k]);
				if (cd_atrb->code[k] != 0)
					imprime_string_pool(cf->constant_pool, cd_atrb->code[k] - 1);

				// atualiza valor de k
				k++;
			}
			printf("\n");
		}
	}
}

/**
 * @brief Imprime no prompt as excpetions info
 * @param cf Referencia para um classFile que representa um .class carregado no array de classes
 * @param exc_atrb Referencia para uma estrutura de expection
 * @return void
 */
void imprime_exc(classFile *cf, exceptions_attribute *exc_atrb)
{
	printf("\n----Exception Info----\n");
	printf("attribute_name_index: cp info #%d ", exc_atrb->attribute_name_index);
	imprime_string_pool(cf->constant_pool, exc_atrb->attribute_name_index - 1);
	printf("\n");
	printf("# - Excecao\n");
	for (int k = 0; k < exc_atrb->number_of_exceptions; k++)
	{
		printf("%d - %d\n", k, exc_atrb->exception_index_table[k]);
	}
}

/**
 * @brief Funcao que acessa a constant pool e acessa as referencias a propria constant pool e imprime no prompt
 * @param cp Referencia a uma constant Pool de um classFile
 * @param pos_pool Indice a ser acessado na constant Pool
 * @return void
 */
void imprime_string_pool(cp_info *cp, int pos_pool)
{
	int tag;
	tag = cp[pos_pool].tag; // pega tag

	if (tag == CONSTANT_Utf8) // se a tag for o de um class info
	{
		printf("%s  ", cp[pos_pool].info.Utf8.bytes); // imprime informacao e sai
		return;
	}

	// Senao, de acordo com a tag, decide qual sera a proxima posicao da CP a ser olhada
	switch (tag)
	{
	case CONSTANT_Class:
		imprime_string_pool(cp, cp[pos_pool].info.Class.name_index - 1);
		break;

	case CONSTANT_Fieldref:
		imprime_string_pool(cp, cp[pos_pool].info.Fieldref.class_index - 1);
		imprime_string_pool(cp, cp[pos_pool].info.Fieldref.name_and_type_index - 1);
		break;

	case CONSTANT_NameAndType:
		imprime_string_pool(cp, cp[pos_pool].info.NameAndType.name_index - 1);
		imprime_string_pool(cp, cp[pos_pool].info.NameAndType.descriptor_index - 1);
		break;

	case CONSTANT_Methodref:
		imprime_string_pool(cp, cp[pos_pool].info.Methodref.class_index - 1);
		imprime_string_pool(cp, cp[pos_pool].info.Methodref.name_and_type_index - 1);
		break;

	case CONSTANT_InterfaceMethodref:
		imprime_string_pool(cp, cp[pos_pool].info.InterfaceMethodref.class_index - 1);
		imprime_string_pool(cp, cp[pos_pool].info.InterfaceMethodref.name_and_type_index - 1);
		break;

	case CONSTANT_String:
		imprime_string_pool(cp, cp[pos_pool].info.String.string_index - 1);
		break;

	case CONSTANT_Integer:
		break; // nunca cai aqui

	case CONSTANT_Float:
		break; // nunca cai aqui

	default:
		break;
	}
}
