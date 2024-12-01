/**
 * Trabalho 1 - PAA 2024.2
 * Questão 1 - Merge Sort
 */

#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

void merge(vector<int> &vetor, int esquerda, int meio, int direita)
{
  int n1 = meio - esquerda + 1;
  int n2 = direita - meio;

  vector<int> L(n1), R(n2);

  for (int i = 0; i < n1; i++)
    L[i] = vetor[esquerda + i];
  for (int i = 0; i < n2; i++)
    R[i] = vetor[meio + 1 + i];

  int i = 0, j = 0, k = esquerda;
  while (i < n1 && j < n2)
  {
    if (L[i] <= R[j])
    {
      vetor[k] = L[i];
      i++;
    }
    else
    {
      vetor[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1)
  {
    vetor[k] = L[i];
    i++;
    k++;
  }

  while (j < n2)
  {
    vetor[k] = R[j];
    j++;
    k++;
  }
}

void mergeSort(vector<int> &vetor, int esquerda, int direita)
{
  if (esquerda < direita)
  {
    int meio = esquerda + (direita - esquerda) / 2;

    mergeSort(vetor, esquerda, meio);
    mergeSort(vetor, meio + 1, direita);

    merge(vetor, esquerda, meio, direita);
  }
}

int main()
{

  vector<int> vetor;
  string linha;

  getline(cin, linha);

  stringstream ss(linha);
  int numero;
  while (ss >> numero)
  {
    vetor.push_back(numero);
  }

  mergeSort(vetor, 0, vetor.size() - 1);

  for (int num : vetor)
    cout << num << " ";
  cout << endl;

  return 0;
}
