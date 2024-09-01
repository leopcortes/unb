#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

const int COD_NRZPOLAR = 1;
const int COD_MANCHESTER = 2;
const int COD_BIPOLAR = 3;
const vector<int> CLK_MANCHESTER{0, 1};

void Transmissor(const string &, int);
vector<int> CodificacaoNRZPolar(vector<int>);
vector<int> CodificacaoManchester(vector<int>);
vector<int> CodificacaoBipolar(vector<int>);

void Receptor(const vector<int> &, int);
vector<int> DecodificacaoNRZPolar(vector<int>);
vector<int> DecodificacaoManchester(vector<int>);
vector<int> DecodificacaoBipolar(vector<int>);
