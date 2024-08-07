#include "CamadaFisica.hpp"

void Transmissor(const string &msgTransmitida, int modulacaoFisica)
{
  vector<int> msgAscii;
  // Impressao do codigo ASCII de cada caractere
  cout << endl
       << "ASCII:" << endl;

  // Conversao de Char para ASCII
  for (unsigned i = 0; i < msgTransmitida.size(); i++)
  {
    vector<int> tempDataCharAscii;
    int charBi = int(msgTransmitida.at(i));

    for (unsigned j = 0; j < 8; j++)
    {
      if (charBi % 2 == 0)
      {
        tempDataCharAscii.push_back(0);
      }
      else
      {
        tempDataCharAscii.push_back(1);
      }
      charBi = charBi >> 1;
    }

    cout << msgTransmitida.at(i) << " - ";

    for (int k = 8 - 1; k >= 0; k--)
    {
      msgAscii.push_back(tempDataCharAscii.at(k));
      cout << tempDataCharAscii.at(k);
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
  }

  // Conversao de volta de ASCII para Char
  string msgRecebida = "";
  int intChar = 0;

  for (unsigned i = 0; i < msgDecodificada.size(); i++)
  {
    if (i != 0 && i % 8 == 0)
    {
      msgRecebida.append(1, char(intChar));
      intChar = 0;
    }
    intChar = intChar << 1;
    intChar += msgDecodificada.at(i);
  }

  msgRecebida.append(1, char(intChar));

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
