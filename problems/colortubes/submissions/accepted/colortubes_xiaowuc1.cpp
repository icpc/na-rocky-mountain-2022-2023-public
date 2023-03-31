#include <array>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<array<int, 2>> ret;
  int n;
  cin >> n;
  vector<vector<int>> tubes(n+1);
  auto domove = [&](int from, int to) -> void {
    assert(from != to);
    assert(tubes[from].size());
    assert(tubes[to].size() < 3);
    ret.push_back({from+1, to+1});
    tubes[to].push_back(tubes[from].back());
    tubes[from].pop_back();
  };
  for(int i = 0; i <= n; i++) {
    for(int j = 0; j < 3; j++) {
      int x;
      cin >> x;
      if(x) tubes[i].push_back(x);
    }
  }
  {
    // phase 1, empty tube n
    int idx = 0;
    while(tubes[n].size()) {
      while(idx < n && tubes[idx].size() == 3) idx++;
      assert(idx < n);
      domove(n, idx);
    }
    assert(tubes[n].size() == 0);
  }
  for(int i = 0; i < n; i++) {
    assert(tubes[i].size() == 3);
    assert(tubes[n].size() == 0);
    if(tubes[i][0] == tubes[i][1] && tubes[i][1] == tubes[i][2]) continue;
    assert(i < n-1);
    const int targetcolor = tubes[i][0];
    // edge case - the topmost color matches but the middle doesn't
    // do some shuffling to ignore this case
    if(tubes[i][1] != targetcolor && tubes[i][2] == targetcolor) {
      domove(i+1, n);
      if(tubes[n].back() == targetcolor) domove(i+1, n);
      domove(i, i+1);
      domove(n, i);
      while(tubes[n].size()) domove(n, i+1);
    }
    int numin = 1 + (tubes[i][1] == targetcolor);
    while(numin < 3) {
      for(int j = i+1; j < n; j++) {
        int present = 2;
        while(present >= 0 && tubes[j][present] != targetcolor) present--;
        if(present < 0) continue;
        // we can always use tube n fully
        numin++;
        if(present >= 1) {
          while(tubes[i].back() != targetcolor) domove(i, n);
          while(tubes[j].back() != targetcolor) domove(j, n);
          assert(tubes[j].back() == targetcolor);
          domove(j, i);
          while(tubes[j].size() < 3) domove(n, j);
          while(tubes[n].size()) domove(n, i);
          break;
        }
        assert(present == 0);
        // it's at the bottom, reverse it
        for(int q = 0; q < 3; q++) domove(j, n);
        // top of n
        while(tubes[i].back() != targetcolor) domove(i, j);
        assert(tubes[n].back() == targetcolor);
        while(tubes[i].size() < 3) domove(n, i);
        while(tubes[j].size() < 3) domove(n, j);
        break;
      }
    }
  }
  cout << ret.size() << "\n";
  for(auto [u, v]: ret) cout << u << " " << v << "\n";
}