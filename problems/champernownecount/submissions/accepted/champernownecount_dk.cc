#include <iostream>
using namespace std;

int main() {
  int N, K;
  while (cin >> N >> K) {
    int ret = 0;
    for (int64_t n = 1, cur = 0, p10 = 10; n <= N; n++) {
      if (n == p10) p10 *= 10;
      cur = (cur*p10+n) % K;
      if (cur == 0) ret++;
    }
    cout << ret << endl;
  }
}
