#include <iostream>

using namespace std;

int digits(int x)
{
  if (x < 10) return 1;
  if (x < 100) return 2;
  if (x < 1000) return 3;
  if (x < 10000) return 4;
  if (x < 100000) return 5;
  return 6;
}

int main()
{
  int N, K;
  cin >> N >> K;

  int64_t val = 0, ans = 0;

  for (int i = 1; i <= N; i++) {
    for (int d = 0; d < digits(i); d++) {
      val *= 10;
      val %= K;
    }
    val += i;
    val %= K;
    if (!val) {
      ans++;
    }
  }

  cout << ans << endl;

  return 0;
}
