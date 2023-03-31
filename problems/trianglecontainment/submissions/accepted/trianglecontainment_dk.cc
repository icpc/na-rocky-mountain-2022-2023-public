#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Point {
  int idx, value;
  int64_t x, y;
  bool operator<(const Point& p) { return x*p.y > p.x*y; }
};

int main() {
  int N, X;
  while (cin >> N >> X) {
    vector<Point> p1, p2;
    for (int i = 0; i < N; i++) {
      int x, y, v;
      cin >> x >> y >> v;
      p1.push_back(Point{i, v, x  , y});
      p2.push_back(Point{i, v, x-X, y});
    }

    sort(p1.begin(), p1.end());
    sort(p2.begin(), p2.end());
    vector<int> p2idx(N);
    for (int i = 0; i < N; i++) p2idx[p2[i].idx] = i;

    vector<int64_t> fenwick(N+1), ret(N);
    int64_t p1value = 0;
    for (auto const& p : p1) {
      int64_t cur = p1value;
      for (int x = p2idx[p.idx]+1; x; x -= x&-x) cur -= fenwick[x];
      ret[p.idx] = cur;
      for (int x = p2idx[p.idx]+1; x <= N; x += x&-x) fenwick[x] += p.value;
      p1value += p.value;
    }
    for (auto x : ret) cout << x << endl;
  }
}
