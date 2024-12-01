/**
 * Trabalho 1 - PAA 2024.2
 * Questão 2 - Insertion Sort
 * Solucao utilizando fast I/O para evitar TLE
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Funcao para fazer a busca binaria e cahar a primeira ocorrencia
int buscaBinaria(const vector<int> &vetor, int desejado)
{
  int esquerda = 0, direita = vetor.size() - 1;
  while (esquerda <= direita)
  {
    int meio = esquerda + (direita - esquerda) / 2;
    if (vetor[meio] == desejado)
    {
      if (meio == 0 || vetor[meio - 1] != desejado)
      {
        return meio;
      }
      else
      {
        direita = meio - 1;
      }
    }
    else if (vetor[meio] < desejado)
    {
      esquerda = meio + 1;
    }
    else
    {
      direita = meio - 1;
    }
  }
  return -1;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int N, Q;
  cin >> N >> Q;

  vector<int> vetor(N);
  for (int i = 0; i < N; ++i)
  {
    cin >> vetor[i];
  }

  while (Q--)
  {
    int query;
    cin >> query;
    cout << buscaBinaria(vetor, query) << "\n";
  }

  return 0;
}
