#include <iostream>
#include <string.h>
#include <string>
#include "romano.h"
using namespace std;

int main(int argc, char const *argv[]){

  if (argc < 2) {
    cout << "Erro ao executar, utilização: " << argv[0] << " <string_do_numero_romano>" << endl;
    return -1;  
  }

  cout << "Número romano original: " << argv[1] << endl;

  cout << "Número romano convertido: " << converter_romano(argv[1]) << endl;

  return 0;
}