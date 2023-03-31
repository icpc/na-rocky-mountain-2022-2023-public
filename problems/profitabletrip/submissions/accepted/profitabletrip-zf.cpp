#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct edge { int v, p; };

int main() {
  int n, m, w;
  cin >> n >> m >> w;

  vector<vector<edge>> g(n+1);
  while (m--) {
    int u, v, p;
    cin >> u >> v >> p;
    g[u].push_back({v,p});
  }

  vector<int> val(n+1, -1e9);

  queue<int> q;

  auto update = [&](int v, int x) {
    if (min(w,x) > val[v]) {
      val[v] = min(w,x);
      q.push(v);
    }
  };

  update(1, 0);

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (auto [v,p] : g[u]) update(v, p+val[u]);
  }

  cout << val[n] << endl;
}
