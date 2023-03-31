#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int goal, start, n;
  cin >> start >> goal >> n;
  vector<array<int, 2>> v(n); // <max size, seconds needed>
  int halflife = 1e9;
  for(auto& x: v) cin >> x[0] >> x[1];
  sort(v.begin(), v.end());
  if(v.back()[0] < start) {
    cout << "-1\n";
    return 0;
  }
  double ret = 0;
  while(v.size()) {
    v.back()[0] = max(v.back()[0], goal);
    if(v.back()[0] < start) {
      assert(halflife < 1e9);
      int nxt = v.back()[0];
      // start * 0.5 ^ (x / halflife) == nxt
      // 0.5 ^ (x / halflife) == nxt / start
      // x / halflife ln 0.5 == ln (nxt / start)
      // x == ln(nxt/start) * halflife / ln(0.5)
      ret += log(nxt/(double)start) * halflife / log(0.5);
      start = nxt;
    }
    halflife = min(halflife, v.back()[1]);
    v.pop_back();
  }
  if(start > goal) {
    ret += log(goal/(double)start) * halflife / log(0.5);
  }
  cout << scientific << setprecision(17) << ret << "\n";
}