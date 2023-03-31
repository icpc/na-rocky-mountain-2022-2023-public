#include <iostream>

using namespace std;

int main()
{
  int R, F;
  cin >> R >> F;

  int turns = F / R, rem = F % R;

  if (rem > R/2) {
    turns++;
  }

  if (turns % 2 == 1) {
    cout << "down" << endl;
  } else {
    cout << "up" << endl;
  }

  return 0;
}
