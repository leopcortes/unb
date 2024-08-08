#include "CamadaFisica.hpp"

void Transmissor(const string &msgTransmitida, int modulacaoFisica)
{
  // Impressao do codigo ASCII de cada caractere
  cout << endl
       << "ASCII:" << endl;

  // Conversao de Char para ASCII
  vector<int> msgAscii;
  for (char ch : msgTransmitida) // Loop for-each para iterar caracteres da string
  {
    int charAscii = static_cast<int>(ch); // Converte o caractere em seu valor inteiro ASCII
    vector<int> tempDataCharAscii(8);     // Vetor para armazenar os 8 bits binarios do caractere

    for (int j = 0; j < 8; j++) // Loop para processar cada bit do valor ASCII do caractere
    {
      tempDataCharAscii[7 - j] = charAscii % 2; // Calcula o bit menos significativo do valor atual de 'charAscii' e o armazena na posicao correta (7-j faz ser do bit mais significativo para o menos significativo)
      charAscii >>= 1;                          // Desloca os bits uma posicao para a direita preparando para a próxima iteracao do loop
    }

    // Impressao do valor ASCII do caractere a armazenamento no vetor msgAscii
    cout << ch << " - ";
    for (int bit : tempDataCharAscii)
    {
      msgAscii.push_back(bit);
      cout << bit;
    }
    cout << endl;
  }

  // Chamada da funcao de codificacao escolhida pelo usuario
  vector<int> msgCodificada;
  switch (modulacaoFisica)
  {
  case COD_NRZPOLAR:
    msgCodificada = CodificacaoNRZPolar(msgAscii);
    break;
  case COD_MANCHESTER:
    msgCodificada = CodificacaoManchester(msgAscii);
    break;
  case COD_BIPOLAR:
    msgCodificada = CodificacaoBipolar(msgAscii);
    break;
  case COD_ASK:
    msgCodificada = CodificacaoASK(msgAscii);
    break;
  case COD_FSK:
    msgCodificada = CodificacaoFSK(msgAscii);
    break;
  case COD_8QAM:
    msgCodificada = Codificacao8QAM(msgAscii);
    break;
  default:
    cout << "Erro na seleção de modulação!" << endl;
    break;
  }

  // Passa a mensagem codificada para o receptor
  Receptor(msgCodificada, modulacaoFisica);
}

vector<int> CodificacaoNRZPolar(vector<int> mensagem)
{
  // Codificacao NRZ-Polar
  // -1 para bit '0'
  //  1 para bit '1'
  cout << endl
       << "NRZ-Polar:";

  for (unsigned i = 0; i < mensagem.size(); i++)
  {
    if (i % 8 == 0)
    {
      cout << endl;
    }
    if (mensagem.at(i) == 0)
    {
      mensagem.at(i) = -1;
      cout << "-1";
    }
    else
    {
      cout << " 1";
    }

    cout << " ";
  }
  cout << endl;

  return mensagem; // Mensagem codificada
}

vector<int> CodificacaoManchester(vector<int> mensagem)
{
  // Codificacao Manchester
  // Transicao de alta para baixa no meio do periodo do bit para bit '0'
  // Transicao de baixa para alta no meio do periodo do bit para bit '1'
  vector<int> codeManchester;
  cout << endl
       << "Manchester:";

  for (unsigned i = 0; i < mensagem.size(); i++)
  {
    codeManchester.push_back(mensagem.at(i) ^ CLK_MANCHESTER.at(0));
    codeManchester.push_back(mensagem.at(i) ^ CLK_MANCHESTER.at(1));

    if (i % 8 == 0)
    {
      cout << endl;
    }

    cout << (mensagem.at(i) ^ CLK_MANCHESTER.at(0));
    cout << (mensagem.at(i) ^ CLK_MANCHESTER.at(1));
  }
  cout << endl;

  return codeManchester; // Mensagem codificada
}

vector<int> CodificacaoBipolar(vector<int> mensagem)
{
  // Codificacao Bipolar
  //   0 para bit '0'
  // +-1 para bit '1'
  bool menosUm = false;
  cout << endl
       << "Bipolar:";

  for (unsigned i = 0; i < mensagem.size(); i++)
  {
    if (i % 8 == 0)
    {
      cout << endl;
    }
    if (mensagem.at(i) == 1)
    {
      if (menosUm)
      {
        mensagem.at(i) = -1;
        cout << "-1";
      }
      else
      {
        cout << " 1";
      }
      menosUm = !menosUm;
    }
    else
    {
      cout << " 0";
    }
    cout << " ";
  }
  cout << endl;

  return mensagem; // Mensagem codificada
}

vector<int> CodificacaoASK(vector<int> mensagem)
{
  // Codificacao Amplitude Shift Keying
}

vector<int> CodificacaoFSK(vector<int> mensagem)
{
  // Codificacao Frequency Shift Keying
}

vector<int> Codificacao8QAM(vector<int> mensagem)
{
  // Codificacao 8-Quadrature Amplitude Modulation
}

void Receptor(const vector<int> &msgCodificada, int modulacaoFisica)
{
  // Chamada da funcao de decodificacao escolhida pelo usuario
  vector<int> msgDecodificada;
  switch (modulacaoFisica)
  {
  case COD_NRZPOLAR:
    msgDecodificada = DecodificacaoNRZPolar(msgCodificada);
    break;
  case COD_MANCHESTER:
    msgDecodificada = DecodificacaoManchester(msgCodificada);
    break;
  case COD_BIPOLAR:
    msgDecodificada = DecodificacaoBipolar(msgCodificada);
    break;
  case COD_FSK:
    msgDecodificada = DecodificacaoASK(msgCodificada);
    break;
  case COD_ASK:
    msgDecodificada = DecodificacaoFSK(msgCodificada);
    break;
  case COD_8QAM:
    msgDecodificada = Decodificacao8QAM(msgCodificada);
    break;
  }

  // Conversao de volta de ASCII para Char
  string msgRecebida;
  int currCharValue = 0;

  for (unsigned i = 0; i < msgDecodificada.size(); ++i) // Percorre cada bit da mensagem decodificada
  {
    currCharValue = (currCharValue << 1) | msgDecodificada[i]; // Desloca o caractere para a esquerda e adiciona o bit atual usando o operador OR
    if ((i + 1) % 8 == 0)                                      // Se 8 bits foram processados
    {
      msgRecebida.push_back(static_cast<char>(currCharValue)); // Converte o valor ASCII para seu caractere e concatena na string
      currCharValue = 0;                                       // Reinicializa variavel auxiliar
    }
  }

  // Adiciona o ultimo caractere reconstruido a string se o tamanho do vetor for um multiplo de 8
  if (msgDecodificada.size() % 8 == 0)
  {
    msgRecebida.push_back(static_cast<char>(currCharValue));
  }

  // Impressao da mensagem recebida (msgTransmitida -> codificacao -> decodificacao -> msgRecebida)
  cout << endl
       << "Mensagem recebida: " << msgRecebida << endl
       << endl;
}

vector<int> DecodificacaoNRZPolar(vector<int> mensagem)
{
  // Decodificacao NRZ-Polar
  // Bit 0 para '-1'
  // Bit 1 para '1'
  for (unsigned i = 0; i < mensagem.size(); i++)
  {
    if (mensagem.at(i) == -1)
    {
      mensagem.at(i) = 0;
    }
  }

  return mensagem; // Mensagem decodificada
}

vector<int> DecodificacaoManchester(vector<int> mensagem)
{
  // Decodificacao Manchester
  // Bit 0 para transicao de 'alta para baixa' no meio do periodo do bit
  // Bit 1 para transicao de 'baixa para alta' no meio do periodo do bit
  vector<int> decodeManchester;
  for (unsigned i = 0; i < mensagem.size(); i += 2)
  {
    decodeManchester.push_back(mensagem.at(i));
  }

  return decodeManchester; // Mensagem decodificada
}

vector<int> DecodificacaoBipolar(vector<int> mensagem)
{
  // Decodificacao Bipolar
  // Bit 0 para '0'
  // Bit 1 para '+-1'
  for (unsigned i = 0; i < mensagem.size(); i++)
  {
    mensagem.at(i) = abs(mensagem.at(i));
  }

  return mensagem; // Mensagem decodificada
}

vector<int> DecodificacaoASK(vector<int> mensagem)
{
  // Decodificacao Amplitude Shift Keying
}

vector<int> DecodificacaoFSK(vector<int> mensagem)
{
  // Decodificacao Frequency Shift Keying
}

vector<int> Decodificacao8QAM(vector<int> mensagem)
{
  // Decodificacao 8-Quadrature Amplitude Modulation
}
