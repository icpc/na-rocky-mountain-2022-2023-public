#include <algorithm>
#include <cassert>
#include <deque>
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
  vector<int> flagged(n, -1);
  int ret = m;
  int id = 0;
  auto good = y_combinator([&](auto self, int curr, deque<array<int, 2>>& ord) -> bool {
    int currid = ++id;
    while(children[curr].size() == 1) {
      flagged[curr] = currid;
      curr = children[curr][0];
    }
    if(children[curr].size() == 0 || ord.size() == 0) return true;
    for(int i = 0; i < children[curr].size() && ord.size(); i++) {
      deque<array<int, 2>> nodes;
      while(ord.size()) {
        auto cand = ord.front();
        if(flagged[cand[0]] == currid || cand[0] == curr) {
          ord.pop_front();
          continue;
        }
        if(lhst[cand[0]] >= lhst[children[curr][i]] && rhst[cand[0]] <= rhst[children[curr][i]]) {
          nodes.push_back(cand);
          ord.pop_front();
        }
        else break;
      }
      if(!self(children[curr][i], nodes)) return false;
    }
    if(ord.size()) {
      ret = min(ret, ord[0][1]);
    }
    return ord.size() == 0;
  });
  {
    int ct = 0;
    auto dfs = y_combinator([&](auto self, int curr) -> void {
      lhst[curr] = ct++;
      for(int out: children[curr]) self(out);
      rhst[curr] = ct++;
    }); dfs(0);
  }
  deque<array<int, 2>> ord;
  for(int i = 0; i < m; i++) {
    int x;
    cin >> x;
    x--;
    if(ord.size() && ord.back()[0] == x) continue;
    ord.push_back({x, i});
  }
  good(0, ord);
  cout << ret << "\n";
}

int main() {
  solve();
}
