// Copyright 2024 - Leonardo P Cortes (200030582)
#include "8_rainhas.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int teste_8_rainhas(const std::string& filename) {
  // Abertura do arquivo_entrada de entrada
  std::ifstream arquivo_entrada(filename);

  // Teste se o arquivo foi aberto corretamente
  if (!arquivo_entrada) {
    return -1;
  }

  std::string linha1, linha2, linha3, linha4, linha5, linha6, linha7, linha8;
  std::string linhaExtra;

  // Leitura das linhas do arquivo
  if (getline(arquivo_entrada, linha1) &&
      getline(arquivo_entrada, linha2) &&
      getline(arquivo_entrada, linha3) &&
      getline(arquivo_entrada, linha4) &&
      getline(arquivo_entrada, linha5) &&
      getline(arquivo_entrada, linha6) &&
      getline(arquivo_entrada, linha7) &&
      getline(arquivo_entrada, linha8) &&
      !getline(arquivo_entrada, linhaExtra)) {
  } else {
    return -1;
  }

  // Fechamento do arquivo_entrada de entrada
  arquivo_entrada.close();

  int valorRetorno = 1;
  int arrayLinha1[8];
  int arrayLinha2[8];
  int arrayLinha3[8];
  int arrayLinha4[8];
  int arrayLinha5[8];
  int arrayLinha6[8];
  int arrayLinha7[8];
  int arrayLinha8[8];

  // Converte os 8 primeiros caracteres da string para inteiros
  int contLinha = 0;
  int contTotal = 0;
  int* arrays[] = { arrayLinha1, arrayLinha2, arrayLinha3, arrayLinha4,
                    arrayLinha5, arrayLinha6, arrayLinha7, arrayLinha8};

  std::vector<std::string> linhas = { linha1, linha2, linha3, linha4,
                            linha5, linha6, linha7, linha8};

  int ataqueMesmaLinha[8] = {10, 10, 10, 10, 10, 10, 10, 10};

  // String para armanzenar os ataques
  std::string ataques = "";

  for (int i=0; i < 8; i++) {
    // Colocando lista em array de inteiros
    contLinha = 0;
    for (int y=0; y < 8; y++) {
      ataqueMesmaLinha[y] = 10;
    }

    for (int j=0; j < 8; j++) {
      if (linhas[i][j] - '0' == 1 || linhas[i][j] - '0' == 0) {
        arrays[i][j] = linhas[i][j] - '0';
        if (arrays[i][j] == 1) {
          contLinha += 1;
          contTotal += 1;
        }
      } else {
        // Caractere diferente de 1 e 0
        return -1;
      }
    }


    // Verificacao de mais de uma rainha na mesma linha
    if (contLinha >=  2) {
      for (int k=0; k < 8; k++) {
        if (arrays[i][k] == 1) {
          for (int a=0; a < 8; a++) {
            if (ataqueMesmaLinha[a] == 10) {
              ataqueMesmaLinha[a] = k;
              break;
            }
          }
        }
      }
      for (int b=0; b < 7; b++) {
        if (ataqueMesmaLinha[b] != 10 && ataqueMesmaLinha[b+1] != 10) {
          ataques += std::to_string(i+1); ataques += ",";
          ataques += std::to_string(ataqueMesmaLinha[b] + 1);
          ataques += "            ";
          ataques += std::to_string(i+1); ataques += ",";
          ataques += std::to_string(ataqueMesmaLinha[b+1] + 1);
          ataques += "\n";
          valorRetorno = 0;
        }
      }
    }
  }

  if (contTotal > 8 || contTotal < 8) {
    return -1;
  }

  // Verificacao de mais de uma rainha na mesma coluna
  bool shouldBreak = false;
  for (int i=0; i < 8; i++) {
    for (int j=0; j < 8; j++) {
      if (arrays[i][j] == 1) {
        shouldBreak =  false;
        for (int k=i; k < 8; k++) {
          for (int l=j; l < 8; l++) {
            if (arrays[k][l] == 1 && i != k && l == j) {
              ataques += std::to_string(i+1); ataques += ",";
              ataques += std::to_string(j+1);
              ataques += "            ";
              ataques += std::to_string(k+1); ataques += ",";
              ataques += std::to_string(l+1); ataques += "\n";

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

  // Verificacao de mais de uma rainha nas diagonais para direita
  int cont = 0;
  for (int i=0; i < 8; i++) {
    for (int j=0; j < 8; j++) {
      if (arrays[i][j] == 1) {
        cont = 1;
        for (int k=i+1; k < 8; k++) {
          if (j+cont >= 8) {
          break;
          }
          if (arrays[k][j+cont] == 1) {
            ataques += std::to_string(i+1); ataques += ",";
            ataques += std::to_string(j+1);
            ataques += "            ";
            ataques += std::to_string(k+1); ataques += ",";
            ataques += std::to_string(j+cont+1); ataques += "\n";
            valorRetorno = 0;
            break;
          }
          cont += 1;
        }
      }
    }
  }

  // Verificacao de mais de uma rainha nas diagonais para esquerda
  cont = 0;
  for (int i=0; i < 8; i++) {
    for (int j=0; j < 8; j++) {
      if (arrays[i][j] == 1) {
        cont = 1;
        for (int k=i+1; k < 8; k++) {
          if (j-cont  <  0) {
            break;
          }
          if (arrays[k][j-cont] == 1) {
            ataques += std::to_string(i+1); ataques += ",";
            ataques += std::to_string(j+1);
            ataques += "            ";
            ataques += std::to_string(k+1); ataques += ",";
            ataques += std::to_string(j-cont+1); ataques += "\n";
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
    std::ofstream arquivo_saida("ataques.txt", std::ios::out);
    if (arquivo_saida.is_open()) {
      arquivo_saida << ataques;
      arquivo_saida.close();
    } else {
      return -1;
    }
  }

  return valorRetorno;
}
