#include "CamadaFisica.hpp"

int main()
{
  // Leitura da mensagem a ser transmitida
  string mensagem;
  int modulacaoFisica = 0;
  cout << "Digite uma mensagem a ser transmitida: ";
  getline(cin, mensagem);

  // Leitura do tipo de modulacao a ser utilizada
  cout << endl
       << COD_NRZPOLAR << " - NRZ-Polar" << endl
       << COD_MANCHESTER << " - Manchester" << endl
       << COD_BIPOLAR << " - Bipolar" << endl
       << "Escolha uma forma de modulação digital: ";
  cin >> modulacaoFisica;

  // Inicio da transmissao
  Transmissor(mensagem, modulacaoFisica);

  return 0;
}
