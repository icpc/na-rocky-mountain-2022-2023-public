#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <complex>
#include <ctime>
#include <cassert>
#include <functional>

using namespace std;

typedef long long ll;
typedef vector<int> VI;
typedef pair<int,int> PII;

#define REP(i,s,t) for(int i=(s);i<(t);i++)
#define FILL(x,v) memset(x,v,sizeof(x))

const int INF = (int)1E9;
#define MAXN 100005

int day[MAXN], incr[MAXN], decr[MAXN];
int main() {
  int N, D;
  cin >> N >> D;
  REP(i,1,N+1) cin >> incr[i] >> decr[i];
  REP(i,1,D+1) cin >> day[i];
  int ans = 0;
  REP(di,1,D+1) {
    int cur = 0, rem = 0;
    multiset<int> vals;
    for (int i = day[di]; i >= day[di - 1] + 1; i--) {
      cur += incr[i];
      if (rem > 0) {
        int c = min(rem, cur);
        rem -= c;
        cur -= c;
      }
      vals.insert(decr[i]);
      while (cur > 0 && vals.size()) {
        auto maxit = vals.rbegin();
        int v = *maxit;
        vals.erase((++maxit).base());
        int c = min(cur, v);
        cur -= c;
        v -= c;
        rem += v;
        ans++;
      }
      if (cur > 0) return puts("-1"), 0;
    }
  }
  cout << ans << endl;
  return 0;
}
