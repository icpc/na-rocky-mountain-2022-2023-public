// An O(n^2) solution
// Used to generate the solutions (but then moved to TLE folder)

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct point {
  ll x, y;
};

// is the turn from p to r about q a CCW turn?
ll ccw(const point& p, const point& q, const point& r) {
  return (p.x-q.x)*(r.y-q.y) > (p.y-q.y)*(r.x-q.x);
}

int main() {
  int n, bx;
  cin >> n >> bx;
  point b = {bx, 0}, o = {0, 0};
  vector<point> p(n);
  vector<ll> val(n);
  for (int i = 0; i < n; ++i) cin >> p[i].x >> p[i].y >> val[i];

  for (int i = 0; i < n; ++i) {
    ll ans = 0;
    for (int j = 0; j < n; ++j)
      if (ccw(p[j], o, p[i]) && !ccw(p[j], b, p[i]))
        ans += val[j];
    cout << ans << endl;
  }

  return 0;
}
