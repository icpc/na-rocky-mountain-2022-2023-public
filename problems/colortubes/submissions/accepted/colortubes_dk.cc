#include <iostream>
#include <vector>
using namespace std;

int N;
vector<vector<int>> T;
vector<int> Zeros;
vector<pair<int, int>> Moves;

void Move(int s, int e) {
  Moves.push_back({s+1, e+1});
  int si, ei;
  for (si = 2; !T[s][si]; si--)
    ;
  for (ei = 0; T[e][ei]; ei++)
    ;
  swap(T[s][si], T[e][ei]);
  for (auto& z : Zeros) if (z == e) { z = s; break; }
}

void Supermove(int s, int si, int e, int ei) {
  if (ei == 1 && si == 0) {
    int m = e+1 + (s==e+1);
    while (!T[m][1]) Move(s, m);
    Supermove(s, si, m,  2);
    Supermove(m,  2, e, ei);
    return;
  }
  while (T[e][ei]) {
    for (auto z : Zeros) if (z != s && z != e) { Move(e, z); break; }
  }
  while (si < 2 && T[s][si+1]) {
    for (auto z : Zeros) if (z != s && z != e) { Move(s, z); break; }
  }
  Move(s, e);
}

int main() {
  while (cin >> N) {
    T = vector<vector<int>>(N+1, {0, 0, 0});
    Zeros.clear();
    for (int i = 0; i <= N; i++) for (auto& x : T[i]) {
      cin >> x;
      if (!x) Zeros.push_back(i);
    }
    for (int i = 0; i < N; i++) {
      if (!T[i][0]) Move(i+1, i);
      int col = T[i][0];
      for (int j = 1; j < 3; j++) if (T[i][j] != col) {
        for (int jj = 2; jj >= 0; jj--) for (int ii = i+1; ii <= N; ii++) if (T[ii][jj] == col) {
          Supermove(ii, jj, i, j);
          goto done;
        }
done:;
      }
    }
    cout << Moves.size() << endl;
    for (auto [s,e] : Moves) cout << s << ' ' << e << endl;
  }
}
