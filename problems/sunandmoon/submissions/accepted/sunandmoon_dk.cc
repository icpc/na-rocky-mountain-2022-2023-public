#include <iostream>
using namespace std;

int main() {
  int Y1, D1, Y2, D2;
  while (cin >> D1 >> Y1 >> D2 >> Y2) {
    for (int y = 1; ; y++) {
      if ((y+D1) % Y1 == 0 && (y+D2) % Y2 == 0) {
        cout << y << endl;
        break;
      }
    }
  }
}
