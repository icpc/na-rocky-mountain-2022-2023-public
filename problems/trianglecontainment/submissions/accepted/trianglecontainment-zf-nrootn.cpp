// An O(n^{1.5}) solution using sqrt decomp.

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

using ll = long long;

// running time will be O(n * (B + n/B))
// B is set to be approximately sqrt(MAXN)
const int B = 320;

struct point {
  ll x, y, val;
  int i;
  bool operator<(const point& rhs) const { return x*rhs.y > y*rhs.x; }
};

int main() {
  int n;
  ll bx;
  cin >> n >> bx;

  vector<point> pts_o(n), pts_b(n);

  for (int i = 0, x, y, v; i < n; ++i) {
    cin >> x >> y >> v;
    pts_o[i] = {x, y, v, i};
    pts_b[i] = {x-bx, y, v, i};
  }


  sort(pts_o.begin(), pts_o.end());
  sort(pts_b.begin(), pts_b.end());
  reverse(pts_b.begin(), pts_b.end());

  // i_to_b[i] is the index in pts_b of i'th point in the input
  vector<int> i_to_b(n);
  for (int i = 0; i < n; ++i) i_to_b[pts_b[i].i] = i;

  vector<ll> val(n, 0), block(n/B+1, 0);
  vector<ll> ans(n);
  ll psum = 0;

  for (point p : pts_o) {
    int ib = i_to_b[p.i];

    ll psum2 = 0;

    int j = ib;
    for (; j%B && j < n; ++j) psum2 += val[j];
    for (; j < n; j += B) psum2 += block[j/B];

    ans[p.i] = psum - psum2;

    val[ib] = p.val;
    block[ib/B] += p.val;
    psum += p.val;
  }

  for (ll x : ans) cout << x << endl;

  return 0;
}
