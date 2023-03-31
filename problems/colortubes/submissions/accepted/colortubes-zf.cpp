// O(n)

#include <iostream>
#include <unordered_set>
#include <vector>
#include <assert.h>

#define MAXN 1100

using namespace std;

int n;
vector<int> tubes[MAXN+1];
unordered_multiset<int> balls[MAXN+1];
vector<pair<int,int>> moves;

// move the top of tube i to tube j
void move(int i, int j) {
  moves.push_back({i+1, j+1});

  assert(tubes[i].size() >= 1 && tubes[j].size() <= 3);

  int clr = tubes[i].back();

  tubes[j].push_back(clr);
  tubes[i].pop_back();

  auto it = balls[clr].find(i);
  assert(it != balls[clr].end());

  balls[clr].erase(it);
  balls[clr].insert(j);
}

// moves balls from tube n to tube i until i is full
void fillup(int i) {
  while (tubes[i].size() < 3) move(n, i);
}

// find another tube containing a ball with the same color
// as the bottom of tube i, assumes tubes[i] is not empty
// and not full of 3 balls with the same color
int other(int i) {
  for (int x : balls[tubes[i][0]]) if (x != i) return x;
  assert(false);
}

// fix test tube i so that the bottom two colours are the same
// assumes tube n is empty, leaves tube n empty
// leaves tubes 0, 1, ..., i-1 untouched
void fix2(int i) {
  assert(tubes[i].size() == 3);

  int clr = tubes[i][0];
  if (tubes[i][1] == clr) return; // already ok

  int j = other(i);

  // expose the bottom of tube i by moving the others to n
  move(i, n);
  move(i, n);

  // explose the ball of the correct color in tube j
  // by moving the others to i, then moving the correct
  // color ball to n
  while (tubes[j].back() != clr) move(j, i);
  move(j, n);

  // expose the bottom of tube i by moving the rest back to j
  while (tubes[i].size() > 1) move(i, j);

  // put the correct color ball in tube i
  move(n, i);

  // cleanup
  fillup(i);
  fillup(j);
}

// fix test tube i so all balls are the same colour
// assumes the bottom 2 are the same colour and tube n is empty
// leaves tube n empty
// leaves tubes 0, 1, ..., i-1 untouched
void fix3(int i) {
  assert(tubes[i].size() == 3);

  int clr = tubes[i][0];
  assert(tubes[i][1] == clr);

  if (tubes[i][2] == clr) return;

  int j = other(i);

  // move the top of tube i to tube n
  move(i, n);

  // expose the correct color ball in tube j by moving the rest
  // to tube n
  while (tubes[j].back() != clr) move(j, n);

  // move this correct color ball to tube i (tube i now has
  // 3 balls with the same color)
  move(j, i);

  // cleanup
  fillup(j);
}

int main() {
  cin >> n;

  for (int i = 0; i <= n; ++i)
    for (int k = 0, x; k < 3; ++k) {
      cin >> x;
      if (x) tubes[i].push_back(x);
      balls[x].insert(i);
    }

  // ensure tube n is empty
  for (int i = 0; i < n; ++i) fillup(i);

  for (int i = 0; i < n-1; ++i) {
    fix2(i);
    fix3(i);
  }

  // sanity check at the end
  for (int i = 0; i < n; ++i) {
    assert(tubes[i].size() == 3);
    int clr = tubes[i][0];
    assert(tubes[i][1] == clr && tubes[i][2] == clr);
    assert(balls[clr].size() == 3);
    for (int x : balls[clr]) assert(x == i);
  }

  cout << moves.size() << endl;
  for (auto p : moves) cout << p.first << ' ' << p.second << endl;

  return 0;
}
