#include <iostream>
#include <map>
#include <vector>

using namespace std;

void ins(map<int, int>& m, int k, int v) {
  auto it = m.upper_bound(k);
  if(it != m.begin()) {
    it--;
    if(it->second <= v) return;
  }
  m[k] = v;
  while(true) {
    auto it = m.upper_bound(k);
    if(it != m.end()) {
      if(it->second >= v) {
        m.erase(it);
        continue;
      }
    }
    break;
  }
}
int main() {
  int n, k;
  cin >> n >> k;
  vector<int> costv(n); 
  vector<int> cleanv(n);
  for (int i = 0; i < n; i++) cin >> costv[i] >> cleanv[i];
  vector<bool> visit(n); while(k--) {int x; cin >> x; visit[--x] = true;}
  map<int, int> dp; dp[0] = 0;
  for(int i = 0; i < n; i++) {
    map<int, int> ndp;
    for(auto [k, v]: dp) {
      int nv = v + costv[i];
      if(!visit[i] || nv == 0) ins(ndp, k, nv);
      nv = max(0, nv - cleanv[i]);
      if(!visit[i] || nv == 0) ins(ndp, k+1, nv);
    }
    dp.swap(ndp);
  }
  if(dp.size() == 0) cout << "-1\n";
  else cout << dp.begin()->first << "\n";
}