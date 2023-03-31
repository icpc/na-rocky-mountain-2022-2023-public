#include <array>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<array<int, 2>> ansv(n);
  set<array<int, 2>> values;
  int k = 0;
  for(int i = 0; i < n; i++) {
    int x;
    cin >> x;
    auto it = values.lower_bound({x, -(1 << 30)});
    if(it == values.begin()) ansv[i] = {x, -(k++)};
    else {
      it--;
      ansv[i] = {x, (*it)[1]};
      values.erase(it);
    }
    values.insert(ansv[i]);
  }
  cout << k << "\n";
  vector<vector<int>> ret(k);
  for(int i = 0; i < n; i++) ret[-ansv[i][1]].push_back(ansv[i][0]);
  for(int i = 0; i < k; i++) for(int j = 0; j < ret[i].size(); j++) cout << ret[i][j] << " \n"[j+1 == ret[i].size()];
}