#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  string S;
  while (cin >> S) {
    vector<int> ret;
    for (int k = 1; k <= S.size(); k++) {
      int score = 0;
      for (int i = 0, ap = 0, bp = 0; i < S.size(); i++) {
        if (S[i] == 'A') {
          if (++ap == k) { score++; ap = bp = 0; }
        } else {
          if (++bp == k) { score--; ap = bp = 0; }
        }
      }
      if (score > 0) ret.push_back(k);
    }
    cout << ret.size() << endl;
    for (int i = 0; i < ret.size(); i++) {
      if (i) cout << ' ';
      cout << ret[i];
    }
    cout << endl;
  }
}
