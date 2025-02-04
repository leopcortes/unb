#include <iostream>
#include <vector>
using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int S, N;
  cin >> S >> N;

  vector<int> pd(S + 1, 0);

  for (int i = 0; i < N; ++i)
  {
    int tamanho, valor;
    cin >> tamanho >> valor;

    for (int j = S; j >= tamanho; --j)
    {
      pd[j] = max(pd[j], pd[j - tamanho] + valor);
    }
  }

  cout << pd[S] << "\n";

  return 0;
}
