// Copyright 2024 - Leonardo P Cortes (200030582)
#include "romanos.hpp"
#include <iostream>
#include <unordered_map>
#include <cstring>

int romanos_para_decimal(char const * num_romano) {
  // Mapa para definir os valores em decimal associados aos romanos
  std::unordered_map<char, int> valores = {
    {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
    {'C', 100}, {'D', 500}, {'M', 1000}
  };

  // Mapa para contar a repetição de cada algarismo
  std::unordered_map<char, int> repeticoes;
  // Variavel para verificar se 'V' foi repetido
  bool v_repetido = false;

  // Variaveis auxiliares
  int num_decimal = 0;
  int tamanho = strlen(num_romano);

  // Verifica se o numero romano tem mais do que 30 caracteres
  if (tamanho > 30) {
    return -1;
  }

  // Percorre cada caractere do numero romano
  for (int i = 0; i < tamanho; ++i) {
    // Verifica se o caractere e um caractere valido (I, V, X, L, C, D, M)
    if (valores.find(num_romano[i]) == valores.end()) {
      return -1;
    }

    // Verifica se o caractere se repete mais de 3 vezes seguidas
    if (i+2 < tamanho-1) {
      if (num_romano[i] == num_romano[i+1] &&
          num_romano[i] == num_romano[i+2] &&
          num_romano[i] == num_romano[i+3]) {
        return -1;
      }
    }

    // Verifica se o caractere 'V' e repetido
    if (num_romano[i] == 'V') {
      if (v_repetido) {
        return -1;
      }
      v_repetido = true;
    }

    int valor_atual = valores[num_romano[i]];

    // Se nao for o primeiro caractere e se o
    // caractere anterior e menor que o caractere atual
    if (i > 0 && valores[num_romano[i-1]] < valor_atual) {
      // 'V' nao pode preceder um caractere maior que ele
      if (num_romano[i-1] == 'V') {
        return -1;
      }
      // Verifica se o caractere anterior e um 'L' ou 'D' e o atual e 'V'
      if ((num_romano[i-1] == 'L' ||
          num_romano[i-1] == 'D') &&
          num_romano[i] == 'V') {
        return -1;
      }
    }

    // Se não for o ultimo caractere e se o valor do caractere
    // atual for menor que o valor do proximo caractere
    if (i < tamanho-1 && valor_atual < valores[num_romano[i+1]]) {
      num_decimal -= valor_atual;  // Subtrai o valor atual do valor total
    } else {
      num_decimal += valor_atual;  // Soma o valor atual ao valor total
    }
  }

  // Verifica se o numero resultante e maior que 3000
  if (num_decimal > 3000) {
    return -1;
  }

  return num_decimal;
}
