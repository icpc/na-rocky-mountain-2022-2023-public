#include <iostream>

using namespace std;

int main()
{
  int d1, y1, d2, y2;
  cin >> d1 >> y1 >> d2 >> y2;

  int c1 = y1-d1;
  while (true) {
    int r2 = c1 - (y2 - d2);
    if (r2 >= 0 && r2 % y2 == 0) {
      cout << c1 << endl;
      return 0;
    }

    c1 += y1;
  }
}
