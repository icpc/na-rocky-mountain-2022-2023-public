#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <vector>

using namespace std;

// BEGIN NO SAD
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define lb lower_bound
#define ub upper_bound
typedef vector<int> vi;
#define f first
#define s second
#define derr if(1) cerr
// END NO SAD

template<class Fun>
class y_combinator_result {
  Fun fun_;
public:
  template<class T>
  explicit y_combinator_result(T &&fun): fun_(std::forward<T>(fun)) {}

  template<class ...Args>
  decltype(auto) operator()(Args &&...args) {
    return fun_(std::ref(*this), std::forward<Args>(args)...);
  }
};

template<class Fun>
decltype(auto) y_combinator(Fun &&fun) {
  return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

template<class T>
bool updmin(T& a, T b) {
  if(b < a) {
    a = b;
    return true;
  }
  return false;
}
template<class T>
bool updmax(T& a, T b) {
  if(b > a) {
    a = b;
    return true;
  }
  return false;
}
typedef int64_t ll;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  int64_t xr;
  cin >> n >> xr;
  vector<array<int64_t, 3>> pts(n); // x, y, v
  for(int i = 0; i < n; i++) cin >> pts[i][0] >> pts[i][1] >> pts[i][2];
  vector<int> ordbyorigin(n); iota(ordbyorigin.begin(), ordbyorigin.end(), 0);
  sort(ordbyorigin.rbegin(), ordbyorigin.rend(), [&](int a, int b) -> bool {
    return pts[a][1] * (pts[b][0] - xr) < (pts[a][0] - xr) * pts[b][1];
  });
  {
    vector<int> t(n);
    for(int i = 0; i < n; i++) t[ordbyorigin[i]] = i;
    ordbyorigin.swap(t);
  }
  vector<int> ord(n); iota(ord.begin(), ord.end(), 0);
  sort(ord.begin(), ord.end(), [&](int a, int b) -> bool {
    return pts[a][1] * pts[b][0] < pts[a][0] * pts[b][1];
  });
  vector<int64_t> ret(n);
  vector<int> included(n);
  bitset<100005> bs;
  ll tot = 0;
  int maxseen = 0;
  for(auto out: ord) {
    if(ordbyorigin[out] > maxseen) {
      ret[out] = tot;
      maxseen = ordbyorigin[out];
    }
    else {
      int curr = bs._Find_first();
      while(curr < ordbyorigin[out]) {
        ret[out] += included[curr];
        curr = bs._Find_next(curr);
      }
    }
    included[ordbyorigin[out]] = pts[out][2];
    tot += pts[out][2];
    bs.set(ordbyorigin[out]);
  }
  for(auto out: ret) cout << out << "\n";
}