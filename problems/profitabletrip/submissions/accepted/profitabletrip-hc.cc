#include <iostream>
#include <algorithm>
#include <climits>
#include <set>
#include <vector>

using namespace std;

int N, M, W;
const int INF = INT_MAX/3;

struct Edge
{
  int to, w;
  Edge(int v_to, int weight)
    : to{v_to}, w{weight} { }
};

vector<vector<Edge>> G;

int main()
{
  cin >> N >> M >> W;

  G.resize(N);
  for (int i = 0; i < M; i++) {
    int u, v, t;
    cin >> u >> v >> t;
    u--;
    v--;
    G[u].emplace_back(v, -t);
  }

  vector<int> D(N, INF);
  D[0] = 0;
  
  set<int> changeset;
  changeset.insert(0);

  while (changeset.size() > 0) {
    set<int> nextset;
    for (auto u : changeset) {
      for (auto e : G[u]) {
	int v = e.to;
	int D2 = max(-W, D[u] + e.w);
	if (D2 < D[v]) {
	  D[v] = D2;
	  nextset.insert(v);
	}
      }
    }
    changeset.swap(nextset);
  }

  cout << -D[N-1] << endl;
  return 0;
}
