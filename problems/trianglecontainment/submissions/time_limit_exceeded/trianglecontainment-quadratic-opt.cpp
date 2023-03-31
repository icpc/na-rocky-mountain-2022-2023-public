// An O(n^2) solution
// Tries to be clever with sorting by y-coordinate and only looking below.
// Also uses fast I/O and static arrays.

#include <bits/stdc++.h>
#define MAXN 100010

using namespace std;

using ll = long long;


struct point {
  ll x, y, v;
  int i;
  bool operator<(const point& rhs) const { return y < rhs.y; }
};

// is the turn from p to r about q a CCW turn?
ll ccw(const point& p, const point& q, const point& r) {
  return (p.x-q.x)*(r.y-q.y) > (p.y-q.y)*(r.x-q.x);
}

point p[MAXN];
ll ans[MAXN];


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, bx;
  cin >> n >> bx;
  point b = {bx, 0, 0, 0}, o = {0, 0, 0, 0};
  for (int i = 0; i < n; ++i) {
    cin >> p[i].x >> p[i].y >> p[i].v;
    p[i].i = i;
  }

  sort(p, p+n);

  for (int i = 0; i < n; ++i) {
    ll tot = 0;
    for (int j = 0; j < i; ++j)
      if (ccw(p[j], o, p[i]) && !ccw(p[j], b, p[i]))
        tot += p[j].v;
    ans[p[i].i] = tot;
  }

  for (int i = 0; i < n; ++i) cout << ans[i] << endl;

  return 0;
}
