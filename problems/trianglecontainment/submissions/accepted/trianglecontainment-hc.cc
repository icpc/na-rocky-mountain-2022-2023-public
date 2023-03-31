#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

typedef long long ll;

#define sz(x) (int)(x).size()

template<typename T>
struct segment {
  int n; T id; function<T(T, T)> op;
  vector<T> S;
  segment(int n, T id, function<T(T, T)> op, const vector<T>& A = {}) 
    : n(n), id(id), op(op), S(2*n, id) {
    for (int i = 0; i < sz(A); i++) S[n+i] = A[i];
    for (int i = n-1; i > 0; i--) S[i] = op(S[2*i], S[2*i+1]);
  }
  // add v to A[x] (can change to = for setting)
  void update(int x, T v) {
    for (S[x += n] += v; x > 1; x /= 2) 
      S[x/2] = op(S[x], S[x^1]);
  }
  // query range A[l], ... , A[r-1].
  T query(int l, int r) {
    T ans = id;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1) ans = op(ans, S[l++]);
      if (r & 1) ans = op(ans, S[--r]);
    }
    return ans;
  }
};

struct Point
{
  ll x, y, v;
  int i;
};

istream &operator>>(istream &is, Point &p)
{
  return is >> p.x >> p.y >> p.v;
}

// sort by "angle" ccw
bool operator<(const Point &p1, const Point &p2)
{
  return p1.y * p2.x < p2.y * p1.x;
}

vector<Point> pts_orig, pts_x;

int main()
{
  int N, X;
  cin >> N >> X;

  pts_orig.resize(N);
  pts_x.resize(N);
  int i = 0;

  for (auto &p : pts_orig) {
    cin >> p;
    p.i = i++;
  }
  
  for (int i = 0; i < N; i++) {
    pts_x[i] = pts_orig[i];
    pts_x[i].x -= X;
  }

  // sort all the points in ccw order from origin
  sort(begin(pts_orig), end(pts_orig));

  // sort all the points in cw order from X
  sort(rbegin(pts_x), rend(pts_x));

  vector<int> xi_to_orig(N);
  for (int i = 0; i < N; i++) {
    xi_to_orig[pts_x[i].i] = i;
  }

  vector<ll> ans(N);
  ll total = 0;           // total value so far

  segment<ll> stadd(N, 0, [] (ll a, ll b) { return a + b; });
  
  // now go through each point in order
  for (auto p : pts_orig) {
    ans[p.i] = total - stadd.query(xi_to_orig[p.i], N);
    stadd.update(xi_to_orig[p.i], p.v);
    total += p.v;
  }

  for (auto v : ans) {
    cout << v << endl;
  }

  return 0;
}
