#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
  vector<vector<int>> ans;
  vector<int> tops;

  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    int index = upper_bound(tops.begin(), tops.end(), -x) - tops.begin();
    if (index >= tops.size()) {
      ans.push_back({-x});
      tops.push_back(-x);
    }
    else {
      ans[index].push_back(-x);
      tops[index] = -x;
    }
  }

  cout << ans.size() << endl;
  for (auto& v : ans)
    for (int i = 0; i < v.size(); ++i)
      cout << -v[i] << (i+1==v.size()?'\n':' ');
}
