#include <iostream>

using namespace std;

int main() {
  int n, k;
  cin >> n >> k;
  int ret = 0;
  int64_t curr = 0;
  for(int i = 1; i <= n; i++) {
    string s = to_string(i);
    for(int a = 0; a < s.size(); a++) curr *= 10;
    curr += i;
    curr %= k;
    ret += curr == 0;
  }
  cout << ret << "\n";
}