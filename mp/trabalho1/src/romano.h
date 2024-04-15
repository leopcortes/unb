#include <iostream>
#include <string.h>
#include <string>
using namespace std;

int valorRomano(char r) {
  switch(r) {
    case 'I': return 1;
    case 'V': return 5;
    case 'X': return 10;
    case 'L': return 50;
    case 'C': return 100;
    case 'D': return 500;
    case 'M': return 1000;
    default: return 0;
  }
}

int converter_romano(string romano_original) {
  int valor = 0;
  int tamanho = romano_original.length();

  for (int i = 0; i < tamanho; i++) {
    int valorAtual = valorRomano(romano_original[i]);

    if (i + 1 < tamanho) {
      int valorProximo = valorRomano(romano_original[i + 1]);

      if (valorAtual >= valorProximo) {
        valor += valorAtual;
      } else {
        valor -= valorAtual;
      }
    } else {
      valor += valorAtual;
    }
  }

  return valor;
}