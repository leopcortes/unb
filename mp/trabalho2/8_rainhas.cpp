// Copyright 2024 - Leonardo P Cortes (200030582)
#include "8_rainhas.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
using std::vector;

int teste_8_rainhas(const string& filename) {
  // int valorRetorno = 0;

  // // Abertura do arquivo
  // string linha; 
  // ifstream arquivo_entrada("teste_8_rainhas.txt"); 
  // if (!arquivo_entrada) {
  //   valorRetorno = -1;
  // } 

  // string linhas[8];

  // // Atribuicao das linhas do arquivo a uma matriz
  // for(int i=0; i<8; i++){
  //   getline(arquivo_entrada, linhas[i]);
  // }

  // arquivo_entrada.close();
  
  // // Verificacao linhas
  // for(int i=0; i<8; i++){
  //   int contRainhas = 0;
  //   string linha = linhas[i];
  //   for(int j=0; j<linha.size(); j++){
  //     if(linha[j] == '1'){
  //       contRainhas++;
  //     }
  //   }
  //   if(contRainhas > 1){
  //     valorRetorno = -3;
  //   }
  //   if(contRainhas < 1){
  //     valorRetorno = -4;
  //   }
  // }

  // // Verificacao colunas
  // for (int col = 0; col < 8; col++) {
  //   int contRainhas = 0;
  //   for (int row = 0; row < 8; row++) {
  //     if (linhas[row][col] == '1') {
  //       contRainhas++;
  //     }
  //   }
  //   if (contRainhas > 1) {
  //     valorRetorno = -5;
  //   }
  //   if (contRainhas < 1) {
  //     valorRetorno = -6;
  //   }
  // }

  // // Impressao da posicao das rainhas que se atacam
  // if (valorRetorno == 0) {
  //   string ataques = "1,3";

  //   ofstream arquivo_saida("ataques.txt", ios::out);
  //   if (arquivo_saida.is_open()) {
  //     arquivo_saida << ataques;
  //     arquivo_saida.close();
  //   } else {
  //     return -2;
  //   }
  // }

  // return valorRetorno;

  ifstream arquivo(filename);

  string linha1, linha2, linha3, linha4, linha5, linha6, linha7, linha8;
  string linhaExtra;

  if (getline(arquivo, linha1) &&
    getline(arquivo, linha2) &&
    getline(arquivo, linha3) &&
    getline(arquivo, linha4) &&
    getline(arquivo, linha5) &&
    getline(arquivo, linha6) &&
    getline(arquivo, linha7) &&
    getline(arquivo, linha8) &&
    !getline(arquivo, linhaExtra)) {
  } else {
    return -1;
  }

  arquivo.close();

  int valorRetorno = 1;
  int arrayLine1[8];
  int arrayLine2[8];
  int arrayLine3[8];
  int arrayLine4[8];
  int arrayLine5[8];
  int arrayLine6[8];
  int arrayLine7[8];
  int arrayLine8[8];

  // Extrai os 8 primeiros caracteres da string e os converte para inteiros
  int countLine = 0;
  int countTotal = 0;
  int* arrays[] = { arrayLine1, arrayLine2, arrayLine3, arrayLine4, arrayLine5, arrayLine6, arrayLine7, arrayLine8};

  vector<string> linhas = { linha1, linha2, linha3, linha4, linha5, linha6, linha7, linha8};

  int attackSameLine[8] = {10, 10, 10, 10, 10, 10, 10, 10};

  string ataques = "";  //  Armazena ataques

  for (int i = 0; i < 8; i++) {
    // Colocando lista em array de inteiros
    countLine = 0;
    for (int y = 0; y < 8; y++) {attackSameLine[y] = 10;}

    for (int j = 0; j < 8; j++) {
      if (linhas[i][j] - '0' == 1 || linhas[i][j] - '0' == 0) {
        arrays[i][j] = linhas[i][j] - '0';
        if (arrays[i][j] == 1) {
          countLine += 1;
          countTotal += 1;
        }
      } else { return -1;}  //  caracter diferente de 1 e 0
    }

    // Verificação ataque mesma linha
    if (countLine >=  2) {
      for (int x = 0; x < 8; x++) {
        if (arrays[i][x] == 1) {
          for (int a = 0; a < 8; a++) {
            if (attackSameLine[a] == 10) {
              attackSameLine[a] = x;
              break;
            }
          }
        }
      }
      for (int b = 0; b < 7; b++) {
        if (attackSameLine[b] != 10 && attackSameLine[b+1] != 10) {
          ataques += to_string(i + 1); ataques += ",";
          ataques += to_string(attackSameLine[b] + 1);
          ataques += "            ";
          ataques += to_string(i + 1); ataques += ",";
          ataques += to_string(attackSameLine[b+1] + 1);
          ataques += "\n";
          valorRetorno = 0;
        }
      }
    }
  }

  if (countTotal > 8 || countTotal < 8) {  //  mais ou menos de 8 rainhas
    return -1;
  }

  // Verificacao colunas
  bool shouldBreak = false;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (arrays[i][j] == 1) {
        shouldBreak =  false;
        for (int y = i; y < 8; y++) {
          for (int x = j; x < 8; x++) {
            if (arrays[y][x] == 1 && i != y && x == j) {
              ataques += to_string(i + 1); ataques += ",";
              ataques += to_string(j + 1);
              ataques += "            ";
              ataques += to_string(y + 1); ataques += ",";
              ataques += to_string(x + 1); ataques += "\n";

              valorRetorno = 0;
              shouldBreak = true;
              break;
            }
          }
          if (shouldBreak) {break;}
        }
      }
    }
  }

  // Verificacao diagonais direita
  int cont = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (arrays[i][j] == 1) {
        cont = 1;
        for (int y = i + 1; y < 8; y++) {
          if (j+cont >= 8) {
          break;
          }
          if (arrays[y][j+cont] == 1) {
            ataques += to_string(i + 1); ataques += ",";
            ataques += to_string(j + 1);
            ataques += "            ";
            ataques += to_string(y + 1); ataques += ",";
            ataques += to_string(j+cont + 1); ataques += "\n";
            valorRetorno = 0;
            break;
          }
          cont += 1;
        }
      }
    }
  }

  // Verificacao diagonais esquerda
  cont = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (arrays[i][j] == 1) {
        cont = 1;
        for (int y = i + 1; y < 8; y++) {
          if (j-cont < 0) {
            break;
          }
          if (arrays[y][j-cont] == 1) {
            ataques += to_string(i + 1); ataques += ",";
            ataques += to_string(j + 1);
            ataques += "            ";
            ataques += to_string(y + 1); ataques += ",";
            ataques += to_string(j-cont + 1); ataques += "\n";
            valorRetorno = 0;
            break;
          }
          cont += 1;
        }
      }
    }
  }

  // Impressao da posicao das rainhas que se atacam
  if (valorRetorno == 0) {
    ofstream arquivo_saida("ataques.txt", ios::out);
    if (arquivo_saida.is_open()) {
      arquivo_saida << ataques;
      arquivo_saida.close();
    } else {
      return -2;
    }
  }

  return valorRetorno;
}
