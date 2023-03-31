#include <array>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

typedef int64_t ll;
const ll INF = 1e18;

int main() {
  int n, m, cap;
  cin >> n >> m >> cap;
  vector<vector<array<int, 2>>> edges(n);
  auto poss = [&](ll thresh) -> bool {
    assert(thresh <= cap);
    vector<ll> dp(n, cap+1);
    dp[n-1] = thresh;
    for(int q = 0; q < n; q++) {
      for(int i = 0; i < n; i++) {
        if(dp[i] > cap) continue;
        for(auto [j, w]: edges[i]) {
          dp[j] = min(dp[j], dp[i] + w);
        }
      }
    }
    while(true) {
      bool upd = false;
      for(int i = 0; i < n; i++) {
        if(dp[i] > cap) continue;
        for(auto [j, w]: edges[i]) {
          if(dp[j] != -INF && dp[i] + w < dp[j]) {
            dp[j] = -INF;
            upd = true;
          }
        }
      }
      if(!upd) break;
    }
    return dp[0] <= 0;
  };
  for(int i = 0; i < m; i++) {
    int a, b, w;
    cin >> a >> b >> w;
    edges[--b].push_back({--a, -w});
  }
  ll lhs = -1e18;
  ll rhs = cap;
  ll ans = cap+1;
  while(lhs <= rhs) {
    ll mid = (lhs+rhs)/2;
    if(poss(mid)) {
      ans = mid;
      lhs = mid + 1;
    }
    else rhs = mid - 1;
  }
  cout << ans << "\n";
}