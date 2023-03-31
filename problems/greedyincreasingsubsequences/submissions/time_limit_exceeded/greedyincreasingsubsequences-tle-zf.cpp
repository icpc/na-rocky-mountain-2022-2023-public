#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 200000;

int a[2][MAXN];
int n[2];

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

  cin >> n[0];
  for (int i = 0; i < n[0]; ++i) cin >> a[0][i];

  vector<vector<int>> ans;

  int ci = 0;

  while (n[ci]) {
    ans.push_back({a[ci][0]});
    n[1-ci] = 0;
    for (int i = 1; i < n[ci]; ++i) {
      if (a[ci][i] > ans.back().back()) ans.back().push_back(a[ci][i]);
      else a[1-ci][n[1-ci]++] = a[ci][i];
    }
    ci = 1-ci;
  }

  cout << ans.size() << endl;
  for (auto& v : ans)
    for (int j = 0; j < v.size(); ++j)
      cout << v[j] << (j+1 == v.size() ? '\n' : ' ');
}
