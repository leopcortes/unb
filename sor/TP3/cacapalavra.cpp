#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <array>
#include <vector>
using namespace std;

ifstream arquivoEntrada;
ofstream arquivoSaida;

int main(int argc, char* argv[]){
    // Criação de variaveis
    int linhaDesejada = 1;
    int linhaAtual = 0;
    string linhaDoArquivo;

    int linhaDesejadaMatriz = 1;
    int linhaAtualMatriz = 0;
    string linhaTamanhoMatriz;
    string linhasMatriz;
    string colunasMatriz;

    vector<string> vetorPalavras;
    int linhaDesejadaPalavras = 1;
    int linhaAtualPalavras = 0;
    string palavraParaBuscar;

    //arquivoEntrada.open("entrada.txt"); // Abertura dos arquivos
    //arquivoSaida.open("saida.txt");

    arquivoEntrada.open(argv[1]); // Abertura dos arquivos por passagem de argumentos na linha de comando
    arquivoSaida.open(argv[2]); 
    if(arquivoEntrada.fail() || arquivoSaida.fail()) { // Verificando se os arquivos foram abertos
        cout << "Erro na abertura do arquivo." << endl;
        return 1;
    }

    while(!arquivoEntrada.eof()){ // Pegando o número de linhas e colunas da matriz da primeira linha do arquivo de entrada e armazenando em 'linhaTamanhoMatriz'
        linhaAtual++;
        getline(arquivoEntrada, linhaTamanhoMatriz);
        if(linhaAtual == linhaDesejada) break;
    }

    linhasMatriz = linhaTamanhoMatriz.substr(0,2); // Primeira string da primeira linha (15)
    colunasMatriz = linhaTamanhoMatriz.substr(3,4); // Segunda string da primeira linha (60)
    int L = stoi(linhasMatriz), C = stoi(colunasMatriz); // Linhas, Colunas

    char matrizChars[L][C]; // Criação da matriz de chars com o tamanho apresentado na primeira linha do arquivo de entrada
    
    for(int i = 0; i < L; i++){ // Para cada linha da matriz
        while(!arquivoEntrada.eof()){
            linhaAtualMatriz++;
            getline(arquivoEntrada, linhaDoArquivo);
            if(linhaAtualMatriz == linhaDesejadaMatriz) break;
        }
        for(int j = 0; j < linhaDoArquivo.length(); j++){ // Para cada coluna (cada caractere da linha)
            matrizChars[i][j] = linhaDoArquivo[j]; // Insere na matriz
        }
        linhaDesejadaMatriz++; // Proxima linha
    }

    for(int k=0; k<6; k++){ // Pegando as 6 palavras a serem procuradas
        while(!arquivoEntrada.eof()){
            linhaAtualPalavras++;
            getline(arquivoEntrada, palavraParaBuscar);
            if(linhaAtualPalavras == linhaDesejadaPalavras) break;
        }
        vetorPalavras.push_back(palavraParaBuscar);
        linhaDesejadaPalavras++;
    }

    for(int linha=0; linha<L; linha++){ 
        for(int coluna=0; coluna<C; coluna++){ // Para cada caractere
            for(int h=0; h<vetorPalavras.size(); h++){ // Para cada palavra a ser procurada, verifica se os 3 primeiros caracteres da palvra sao iguais aos da matriz (procura nas 8 direcoes possiveis), se for transforma o caractere em CAPS
                if((matrizChars[linha][coluna+1] == vetorPalavras[h][1] && matrizChars[linha][coluna+2] == vetorPalavras[h][2] && matrizChars[linha][coluna+3] == vetorPalavras[h][3] && matrizChars[linha][coluna+4] == vetorPalavras[h][4])){
                    for(int k=0; k<vetorPalavras[h].length(); k++){
                        matrizChars[linha][coluna+k] = char(toupper(matrizChars[linha][coluna+k]));
                    }
                }
                else if((matrizChars[linha][coluna] == vetorPalavras[h][0] && matrizChars[linha][coluna-1] == vetorPalavras[h][1] && matrizChars[linha][coluna-2] == vetorPalavras[h][2] && matrizChars[linha][coluna-3] == vetorPalavras[h][3])){
                    for(int k=0; k<vetorPalavras[h].length(); k++){
                        matrizChars[linha][coluna-k] = char(toupper(matrizChars[linha][coluna-k]));
                    }
                }
                else if((matrizChars[linha][coluna] == vetorPalavras[h][0] && matrizChars[linha+1][coluna] == vetorPalavras[h][1] && matrizChars[linha+2][coluna] == vetorPalavras[h][2] && matrizChars[linha+3][coluna] == vetorPalavras[h][3])){
                    for(int k=0; k<vetorPalavras[h].length(); k++){
                        matrizChars[linha+k][coluna] = char(toupper(matrizChars[linha+k][coluna]));
                    }
                }
                else if((matrizChars[linha][coluna] == vetorPalavras[h][0] && matrizChars[linha-1][coluna] == vetorPalavras[h][1] && matrizChars[linha-2][coluna] == vetorPalavras[h][2] && matrizChars[linha-3][coluna] == vetorPalavras[h][3])){
                    for(int k=0; k<vetorPalavras[h].length(); k++){
                        matrizChars[linha-k][coluna] = char(toupper(matrizChars[linha-k][coluna]));
                    }
                }
                else if((matrizChars[linha][coluna] == vetorPalavras[h][0] && matrizChars[linha-1][coluna-1] == vetorPalavras[h][1] && matrizChars[linha-2][coluna-2] == vetorPalavras[h][2] && matrizChars[linha-3][coluna-3] == vetorPalavras[h][3])){
                    for(int k=0; k<vetorPalavras[h].length(); k++){
                        matrizChars[linha-k][coluna-k] = char(toupper(matrizChars[linha-k][coluna-k]));
                    }
                }
                else if((matrizChars[linha][coluna] == vetorPalavras[h][0] && matrizChars[linha-1][coluna+1] == vetorPalavras[h][1] && matrizChars[linha-2][coluna+2] == vetorPalavras[h][2] && matrizChars[linha-3][coluna+3] == vetorPalavras[h][3])){
                    for(int k=0; k<vetorPalavras[h].length(); k++){
                        matrizChars[linha-k][coluna+k] = char(toupper(matrizChars[linha-k][coluna+k]));
                    }
                }
                else if((matrizChars[linha][coluna] == vetorPalavras[h][0] && matrizChars[linha+1][coluna+1] == vetorPalavras[h][1] && matrizChars[linha+2][coluna+2] == vetorPalavras[h][2] && matrizChars[linha+3][coluna+3] == vetorPalavras[h][3])){
                    for(int k=0; k<vetorPalavras[h].length(); k++){
                        matrizChars[linha+k][coluna+k] = char(toupper(matrizChars[linha+k][coluna+k]));
                    }
                }
                else if((matrizChars[linha][coluna] == vetorPalavras[h][0] && matrizChars[linha+1][coluna-1] == vetorPalavras[h][1] && matrizChars[linha+2][coluna-2] == vetorPalavras[h][2] && matrizChars[linha+3][coluna-3] == vetorPalavras[h][3])){
                    for(int k=0; k<vetorPalavras[h].length(); k++){
                        matrizChars[linha+k][coluna-k] = char(toupper(matrizChars[linha+k][coluna-k]));
                    }
                }
                else {
                    matrizChars[linha][coluna] = matrizChars[linha][coluna]; // Se nao for, mantem o caractere normal
                }
            }
        }
    }
    
    for(int linha=0; linha<L; linha++){ // Impressao da matriz completa
        for(int coluna=0; coluna<C; coluna++){
            arquivoSaida << matrizChars[linha][coluna];
        }
        arquivoSaida << endl;
    }

    return 0;
}