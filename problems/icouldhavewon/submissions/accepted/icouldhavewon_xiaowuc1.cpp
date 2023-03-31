#include <iostream>
#include <vector>

using namespace std;

int main() {
  string s;
  cin >> s;
  vector<int> ret;
  for(int k = 1; k <= s.size(); k++) {
    int ar = 0;
    int br = 0;
    int ac = 0;
    int bc = 0;
    for(auto out: s) {
      if(out == 'A') ac++;
      else bc++;
      if(ac == k) {
        ar++; ac = 0; bc = 0;
      }
      if(bc == k) {
        br++; ac = 0; bc = 0;
      }
    }
    if(ar > br) ret.push_back(k);
  }
  cout << ret.size() << "\n";
  for(int i = 0; i < ret.size(); i++) cout << ret[i] << " \n"[i == ret.size()-1];
}