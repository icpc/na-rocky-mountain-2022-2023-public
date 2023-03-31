#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> A;
vector<pair<int,int>> moves;

void move(int i, int j) {
  moves.emplace_back(i, j);
  A[j].push_back(A[i].back());
  A[i].pop_back();
}

void rotatex(int x, int y, int z) {
  move(x, y);
  move(x, z);
  move(x, z);
  move(y, x);
  move(z, x);
  move(z, x);
}

void flipx(int x, int y, int z) {
  move(x, y);
  move(x, z);
  move(y, x);
  move(z, x);
}

void rotateorflipx(int x, int y, int z) {
  if(A[x][2] != A[x][0]) rotatex(x, y, z);
  else flipx(x, y, z);
}

void swapxy(int x, int y, int z) {
  move(x, z);
  move(y, x);
  move(z, y);
}

void do_case() {
  int n; cin >> n;
  A.resize(n + 1);
  vector<int> missing;
  for(int j=0;j<n+1;j++)
    for(int i=0;i<3;i++) {
      int x; cin >> x;
      if(x == 0) missing.push_back(j);
      else A[j].push_back(x - 1);
    }
  
  while(missing.size() && missing.back() == n) missing.pop_back();

  while(missing.size()) {
    move(n, missing.back());
    missing.pop_back();
  }
  move(n-1, n);

  for(int i=0;i<n-1;i++) {
    while(A[i] != vector<int>({i, i, i})) {
      int val = A[i].back();
      if(val == i) {
        rotateorflipx(i, n-1, n);
        continue;
      }
      if(val == n-1) {
        if(A[n][0] != n-1) swapxy(i, n, n-1);
        else if(A[n-1][1] != n-1) swapxy(i, n-1, n);
        else {
          move(n-1, n);
          swapxy(i, n-1, n);
          move(n, n-1);
        }
      } else {
        if(A[val].back() == val) rotateorflipx(val, n-1, n);
        swapxy(i, val, n-1);
      }
    }
  }
  move(n, n-1);
}

int main() {
  do_case();
  cout << moves.size() << endl;
  for(auto [x, y] : moves) cout << x + 1 << " " << y + 1 << endl;
}
