#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

template<class Fun>
class y_combinator_result {
  Fun fun_;
public:
  template<class T>
  explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}

  template<class ...Args>
  decltype(auto) operator()(Args &&...args) {
    return fun_(std::ref(*this), std::forward<Args>(args)...);
  }
};

template<class Fun>
decltype(auto) y_combinator(Fun &&fun) {
  return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> children(n);
  for(int i = 1; i < n; i++) {
    int a, b;
    cin >> a >> b;
    children[--a].push_back(--b);
  }
  for(int i = 0; i < n; i++) sort(children[i].begin(), children[i].end());
  vector<int> lhst(n, -1), rhst(n, -1);
  {
    int ct = 0;
    auto dfs = y_combinator([&](auto self, int curr) -> void {
      lhst[curr] = ct++;
      for(int out: children[curr]) self(out);
      rhst[curr] = ct++;
    }); dfs(0);
  }
  vector<int> ord(m);
  for(auto& x: ord) {
    cin >> x; x--;
  }
  int nowt = 0;
  int ans = 0;
  for(int curr: ord) {
    if(nowt > rhst[curr]) {
      cout << ans << "\n";
      return;
    }
    nowt = max(nowt, lhst[curr]);
    ans++;
  }
  cout << ans << "\n";
}

int main() {
  solve();
}
