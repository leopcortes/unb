#include "romanos.hpp"
#include <iostream>
#include <unordered_map>
#include <cstring>
using namespace std;

int romanos_para_decimal(char const * num_romano){
  unordered_map<char, int> valores = {
    {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}
  };

  // Mapa para contar a repetição de cada algarismo
  unordered_map<char, int> repeticoes;
  bool v_repetido = false; // Verifica se 'V' foi repetido
  
  int num_decimal = 0;
  int tamanho = strlen(num_romano);

  // Verifica se o numero romano tem mais do que 30 caracteres
  if (tamanho > 30) {
    return -1;
  }

  // Percorre cada caractere do numero romano
  for (int i = 0; i < tamanho; ++i) {
    // Verifica se o caractere e um caractere valido
    if (valores.find(num_romano[i]) == valores.end()) {
      return -1;
    }

    int valor_atual = valores[num_romano[i]];

    // Conta as repeticoes do algarismo
    if (repeticoes.find(num_romano[i]) == repeticoes.end()) {
      repeticoes[num_romano[i]] = 1;
    } else {
      repeticoes[num_romano[i]]++;
    }

    // Verifica se o algarismo atual se repete mais de 3 vezes
    if (repeticoes[num_romano[i]] > 3) {
      return -1;
    }

    // Verifica regra específica para o caractere 'V'
    if (num_romano[i] == 'V') {
      if (v_repetido) {
        return -1; // 'V' repetido
      }
      v_repetido = true;
    }

    // Verifica regra de precedência
    if (i > 0 && valores[num_romano[i - 1]] < valor_atual) {
      // Verifica se o caractere anterior é um 'V'
      if (num_romano[i - 1] == 'V') {
        return -1; // 'V' não pode preceder um caractere maior que ele
      }
      // Verifica se o caractere anterior é um 'L' ou 'D' e o atual é 'V'
      if ((num_romano[i - 1] == 'L' || num_romano[i - 1] == 'D') && num_romano[i] == 'V') {
        return -1; // 'V' não pode seguir 'L' ou 'D'
      }
    }
    
    // Se não for o ultimo caractere e se o valor do caractere atual for menor que o valor do proximo caractere
    if (i < tamanho-1 && valor_atual < valores[num_romano[i+1]]) {
      num_decimal -= valor_atual; // Subtrai o valor atual do valor total
    } else {
      num_decimal += valor_atual; // Soma o valor atual ao valor total
    }
  }

  // Verifica se o numero resultante é maior que 3000
  if (num_decimal > 3000) {
    return -1;
  }

  return num_decimal;
}