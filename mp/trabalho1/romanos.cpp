#include "romanos.hpp"

int valor_romano(char r) {
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

int romanos_para_decimal(char const * num_romano) {

}
 