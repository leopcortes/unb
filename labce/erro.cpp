#include <iostream>
#include <iomanip>
using namespace std;

int main(){

    double valorCalculado;
    double valorMedido;
    double erro;

    while(1) {
        cout << "Valor Calculado: ";
        cin >> valorCalculado;
        cout << "Valor Medido: ";
        cin >> valorMedido;

        erro = ((valorCalculado - valorMedido) / valorCalculado) * 100;
        
        cout << "Erro = " << setprecision(3) << fixed << erro << "%" << endl << endl;
    }

    return 0;
}