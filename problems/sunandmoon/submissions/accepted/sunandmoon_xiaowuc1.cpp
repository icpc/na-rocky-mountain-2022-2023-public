#include <iostream>

using namespace std;

int main() {
  int ya, da, yb, db;
  cin >> da >> ya >> db >> yb;
  int ret = 0;
  do {
    if(++da == ya) da = 0;
    if(++db == yb) db = 0;
    ret++;
    if(da == 0 && db == 0) {
      cout << ret << "\n";
      break;
    }
  }
  while(true);
}