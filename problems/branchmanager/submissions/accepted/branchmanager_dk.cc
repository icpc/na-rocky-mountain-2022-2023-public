#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int N, M;
  while (cin >> N >> M) {
    vector<vector<int>> ch(N+1);
    vector<int> D(M), par(N+1);
    for (int i = 0; i < N-1; i++) {
      int a, b;
      cin >> a >> b;
      ch[a].push_back(b);
      par[b] = a;
    }
    for (auto& x : D) cin >> x;
    for (auto& v : ch) sort(v.begin(), v.end(), greater<int>());

    vector<int> seen(N+1);
    function<void(int,int)> rec = [&](int x, int v) {
      seen[x] = v;
      if (ch[x].size()) rec(ch[x].back(), v);
    };
    rec(1, 1);

    int ret = 0;
    for (auto& d : D) {
      vector<int> path;
      int x = d;
      for (; !seen[x]; x = par[x]) path.push_back(x);
      if (seen[x] == 2) goto done;
      while (path.size()) {
        if (ch[x].size() <= 1) goto done;
        rec(ch[x].back(), 2);
        ch[x].pop_back();
        rec(ch[x].back(), 1);
        while (path.size() && path.back() == ch[x].back()) {
          x = path.back();
          path.pop_back();
        }
      }
      ret++;
    }
done:
    cout << ret << endl;
  }
}
