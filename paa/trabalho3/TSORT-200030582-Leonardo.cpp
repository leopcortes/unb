#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 1'000'001;

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  vector<int> freq(MAX_N, 0);

  for (int i = 0; i < t; ++i)
  {
    int num;
    cin >> num;
    freq[num]++;
  }

  for (int i = 0; i < MAX_N; ++i)
  {
    while (freq[i] > 0)
    {
      cout << i << "\n";
      freq[i]--;
    }
  }

  return 0;
}