#include "romanos.hpp"
#include <iostream>
#include <unordered_map>
#include <cstring>
using namespace std;

int romanos_para_decimal(char const * num_romano){
  unordered_map<char, int> valores = {
    {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
    {'C', 100}, {'D', 500}, {'M', 1000}
  };
  
  int num_decimal = 0;
  int tamanho = strlen(num_romano);

  for (int i = 0; i < tamanho; ++i) {
    int valor_atual = valores[num_romano[i]];
    
    if (i < tamanho-1 && valor_atual < valores[num_romano[i+1]]) {
      num_decimal -= valor_atual;
    } else {
      num_decimal += valor_atual;
    }
  }

  return num_decimal;
}