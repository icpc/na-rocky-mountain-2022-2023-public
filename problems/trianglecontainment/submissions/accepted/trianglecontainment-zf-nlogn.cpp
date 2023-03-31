// An O(n log n) solution.
// Uses the KACTL segment tree implementation with license CC0.
// https://github.com/kth-competitive-programming/kactl

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

using ll = long long;

// This struct is from KACTL, see reference above.
// Modified to handle + instead of min and to store long long
struct Tree {
	typedef ll T;
	static constexpr T unit = 0;
	T f(T a, T b) { return a+b; } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

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

  Tree t(n, 0);
  vector<ll> ans(n);
  ll psum = 0;

  for (point p : pts_o) {
    int ib = i_to_b[p.i];
    ans[p.i] = psum - t.query(ib, n);
    t.update(ib, p.val);
    psum += p.val;
  }

  for (ll x : ans) cout << x << endl;

  return 0;
}
