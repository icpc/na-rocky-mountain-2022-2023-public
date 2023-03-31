// apply Bellman-Ford iterations until it stabilizes

#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e9;

struct edge { int u, v, p; };

int main() {
  int n, m, w;
  cin >> n >> m >> w;

  vector<edge> edges(m);
  for (edge& e : edges) cin >> e.u >> e.v >> e.p;

  vector<int> val(n+1, -INF);

  val[1] = 0;

  bool change = true;
  while (change) {
    change = false;
    for (const edge& e : edges)
      if (val[e.u] > -INF) {
        int nval = min(w, val[e.u] + e.p);
        if (nval > val[e.v]) {
          change = true;
          val[e.v] = nval;
        }
      }
  }

  cout << val[n] << endl;
}
