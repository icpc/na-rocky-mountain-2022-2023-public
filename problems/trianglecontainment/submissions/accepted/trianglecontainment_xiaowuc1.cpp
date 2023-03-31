#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

struct seg {
  int SZ;
  vector<int64_t> rt;
  seg() {
    SZ = 1 << 17;
    rt.resize(2*SZ);
  }
  void upd(int idx, int val) {
    idx += SZ;
    while(idx) {
      rt[idx] += val;
      idx /= 2;
    }
  }
  int64_t qry(int lhs, int rhs) {
    int64_t ret = 0;
    lhs += SZ;
    rhs += SZ;
    while(lhs <= rhs) {
      if(lhs%2) ret += rt[lhs++];
      if(rhs%2==0) ret += rt[rhs--];
      lhs /= 2;
      rhs /= 2;
    }
    return ret;
  }
};

int main() {
  int n;
  int64_t xr;
  cin >> n >> xr;
  vector<array<int64_t, 3>> pts(n); // x, y, v
  for(int i = 0; i < n; i++) cin >> pts[i][0] >> pts[i][1] >> pts[i][2];
  vector<int> ordbyorigin(n); iota(ordbyorigin.begin(), ordbyorigin.end(), 0);
  sort(ordbyorigin.begin(), ordbyorigin.end(), [&](int a, int b) -> bool {
    return pts[a][1] * pts[b][0] < pts[a][0] * pts[b][1];
    // return atan2(pts[a][1], pts[a][0]) < atan2(pts[b][1], pts[b][0]);
  });
  {
    vector<int> t(n);
    for(int i = 0; i < n; i++) t[ordbyorigin[i]] = i;
    ordbyorigin.swap(t);
  }
  vector<int> ord(n); iota(ord.begin(), ord.end(), 0);
  sort(ord.rbegin(), ord.rend(), [&](int a, int b) -> bool {
    return pts[a][1] * (pts[b][0] - xr) < (pts[a][0] - xr) * pts[b][1];
  });
  vector<int64_t> ret(n);
  seg segt;
  for(auto out: ord) {
    ret[out] = segt.qry(0, ordbyorigin[out]-1);
    segt.upd(ordbyorigin[out], pts[out][2]);
  }
  for(auto out: ret) cout << out << "\n";
}