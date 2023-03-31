#include <iostream>

using namespace std;

int gcd(int a, int b, int &s, int &t) { // a*s+b*t = g
  if (b==0) { t = 0; s = (a < 0) ? -1 : 1; return (a < 0) ? -a : a;
  } else { int g = gcd(b, a%b, t, s);  t -= a/b*s;  return g; }
}

int ceildiv(int num, int den)
{
  int sign = 1;
  if (num < 0) {
    num *= -1;
    sign *= -1;
  }
  if (den < 0) {
    den *= -1;
    sign *= -1;
  }

  if (sign > 0) {
    return (num + den - 1) / den;
  } else {
    return -(num / den);
  }
}

int main()
{
  int d1, y1, d2, y2;
  cin >> d1 >> y1 >> d2 >> y2;

  // y1-d1 + s*y1 = y2-d2+t*y2
  //  s*y1 - t*y2 = y2 - d2 - y1 + d1

  int rhs = y2 - d2 - y1 + d1;
  int s, t;
  int g = gcd(y1, -y2, s, t);

  if (rhs % g != 0) {
    cout << "Bad input!" << endl;
  }

  s *= rhs/g;
  t *= rhs/g;

  // solns are
  //
  // s + k * y2/g >= 0
  // t + k * y1/g >= 0
  int k = max(ceildiv(-s * g, y2), ceildiv(-t * g, y1));
  
  int ans = y1 - d1 + (s + k * y2/g) * y1;
  cout << ans << endl;
  return 0;
}
