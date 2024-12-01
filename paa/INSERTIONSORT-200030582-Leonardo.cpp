/**
 * Trabalho 1 - PAA 2024.2
 * Questão 2 - Insertion Sort
 * Solucao utilizando Fenwick Tree pois a tentativa com merge sort falhou (TLE)
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Funcao para atualizar a Fenwick Tree no indice index
void update(vector<int> &fenwick, int index, int tamanho, int delta)
{
  while (index <= tamanho)
  {
    fenwick[index] += delta;
    index += index & -index;
  }
}

// Funcao para consultar o prefixo acumulado na Fenwick Tree ate o indice index
int query(const vector<int> &fenwick, int index)
{
  int sum = 0;
  while (index > 0)
  {
    sum += fenwick[index];
    index -= index & -index;
  }
  return sum;
}

// Funcao para contar o numero de trocas necessarias para ordenar o vetor
int contaTrocas(const vector<int> &vetor)
{
  int tam = vetor.size();
  int elementoMax = *max_element(vetor.begin(), vetor.end());

  vector<int> fenwick(elementoMax + 1, 0);

  int trocas = 0;

  for (int i = tam - 1; i >= 0; --i)
  {
    trocas += query(fenwick, vetor[i] - 1);
    update(fenwick, vetor[i], elementoMax, 1);
  }

  return trocas;
}

int main()
{
  int qntTestes;
  cin >> qntTestes;

  while (qntTestes--)
  {
    int qntNumeros;
    cin >> qntNumeros;
    vector<int> vetor(qntNumeros);
    for (int i = 0; i < qntNumeros; ++i)
    {
      cin >> vetor[i];
    }

    cout << contaTrocas(vetor) << endl;
  }

  return 0;
}
