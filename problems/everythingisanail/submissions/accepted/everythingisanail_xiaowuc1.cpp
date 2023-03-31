#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int dp[8][3];
int main() {
  int n;
  cin >> n;
  vector<int> v(n);
  for(auto& x: v) {
    cin >> x;
  }
  for(auto out: v) {
    for(int mask = 0; mask < 8; mask++) {
      for(int i = 0; i < 3; i++) {
        if((mask&(1<<i))) {
          dp[mask][i] += (i == out);
          if(i == out) {
            for(int j = 0; j < 3; j++) {
              if(mask&(1<<j)) continue;
              dp[mask][i] = max(dp[mask][i], dp[mask|(1<<j)][j] + 1);
            }
          }
        }
      }
    }
  }
  int ret = 0;
  for(int i = 0; i < 8; i++) for(int j = 0; j < 3; j++) ret = max(ret, dp[i][j]);
  cout << ret << "\n";
}