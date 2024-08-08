#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

const int COD_NRZPOLAR = 1;
const int COD_MANCHESTER = 2;
const int COD_BIPOLAR = 3;
const int COD_ASK = 4;
const int COD_FSK = 5;
const int COD_8QAM = 6;
const vector<int> CLK_MANCHESTER{0, 1};

void Transmissor(const string &, int);
vector<int> CodificacaoNRZPolar(vector<int>);
vector<int> CodificacaoManchester(vector<int>);
vector<int> CodificacaoBipolar(vector<int>);
vector<int> CodificacaoASK(vector<int>);
vector<int> CodificacaoFSK(vector<int>);
vector<int> Codificacao8QAM(vector<int>);

void Receptor(const vector<int> &, int);
vector<int> DecodificacaoNRZPolar(vector<int>);
vector<int> DecodificacaoManchester(vector<int>);
vector<int> DecodificacaoBipolar(vector<int>);
vector<int> DecodificacaoASK(vector<int>);
vector<int> DecodificacaoFSK(vector<int>);
vector<int> Decodificacao8QAM(vector<int>);
