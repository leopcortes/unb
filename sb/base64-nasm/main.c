#include <stdio.h>
#include <stdlib.h>

extern char *BASE64_encode(char *input, int input_size, int  *output_size);
extern char *BASE64_decode(char *input, int input_size, int *output_size);

int main(int argc, char* argv[])
{
    
    if (argc < 4) {
        printf("Uso: %s <e/d> <arquivo_de_entrada> <arquivo_de_saida> ...\n", argv[0]);
        return 1;
    }
    
    char* mode = argv[1];
    //char* mode = "d";
    //seguranca mandou abraco
    char* arquivo_entrada = argv[2];
    //char* arquivo_entrada = "saida.txt";
    // Abrindo o arquivo de entrada para leitura
    FILE *input_file = fopen(arquivo_entrada, "rb");
    if (input_file == NULL)
    {
        perror("Erro ao abrir o arquivo de entrada");
        return 1;
    }

    // Determinando o tamanho do arquivo
    fseek(input_file, 0, SEEK_END);
    size_t input_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    // Alocando memoria para ler arquivo
    char *base = (char *)malloc(input_size + 1);
    if (base == NULL)
    {
        perror("Erro ao alocar memória");
        fclose(input_file);
        return 1;
    }

    // Lendo o conteudo do arquivo
    fread(base, 1, input_size, input_file);
    base[input_size] = '\0';
    fclose(input_file);

    // Codificando em Base64
    int output_size;
    char *ret;
    if(*mode == 'e')
        ret = BASE64_encode(base, input_size-1, &output_size);
    else if(*mode == 'd')
        ret = BASE64_decode(base, input_size, &output_size);

    char* arquivo_saida = argv[3];
    //char* arquivo_saida = "saida2.txt";
    // Abrindo o arquivo de saida para escrita
    FILE *output_file = fopen(arquivo_saida, "wb");
    if (output_file == NULL)
    {
        perror("Erro ao abrir o arquivo de saída");
        free(base);
        return 1;
    }

    // Escrevendo o tamanho da saida e a saida codificada no arquiv
    fprintf(output_file,"%s",ret);
    fclose(output_file);

    // Liberando memoria alocada
    free(base);
    free(ret);

    return 0;
}

