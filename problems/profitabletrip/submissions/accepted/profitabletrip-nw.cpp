#include <vector>
#include <stack>
#include <iostream>
using namespace std;
vector<pair<int,int>> adj[2002];
int best[2002];
int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    int n,m,w;
    cin >> n >> m >> w;
    for (int i = 0; i < m; i++) {
        int u,v,t;
        cin >> u >> v >> t;
        adj[u].emplace_back(v,t);
    }
    stack<int> q;
    q.push(1);
    fill(best, best+n+1, -2000000000);
    best[1] = 0;
    while (!q.empty()) {
        int u = q.top(); q.pop();
        for (auto v : adj[u]) {
            int val = min(w, v.second+best[u]);
            if (best[v.first] < val) {
                best[v.first] = val;
                q.push(v.first);
            }
        }
    }
    cout << best[n] << endl;
}
