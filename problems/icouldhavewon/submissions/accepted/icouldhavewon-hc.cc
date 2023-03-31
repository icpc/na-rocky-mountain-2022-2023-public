#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
  string s;
  cin >> s;
  int n = s.length();

  vector<int> ans;
  for (int k = 1; k <= n; k++) {
    int win[2] = {0};
    int score[2] = {0};

    for (auto c : s) {
      if (++score[c-'A'] == k) {
	win[c-'A']++;
	score[0] = score[1] = 0;
      }
    }
    if (win[0] > win[1]) {
      ans.push_back(k);
    }
  }

  cout << ans.size() << endl;
  for (auto k : ans) {
    cout << k << ' ';
  }
  cout << endl;

  return 0;
}
