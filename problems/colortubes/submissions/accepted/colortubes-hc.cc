#include <iostream>
#include <vector>
#include <assert.h>
#include <set>

using namespace std;

typedef pair<int,int> pii;
vector<pii> moves;

int n;
int tube[1001][3];
int tsize[1001] = {0};

void do_move(int src, int dest, set<int> &has_room)
{
  assert(tsize[src] > 0 && tsize[dest] < 3);
  int ball = tube[src][--tsize[src]];
  tube[dest][tsize[dest]++] = ball;

  has_room.insert(src);
  if (tsize[dest] == 3) has_room.erase(dest);
  moves.emplace_back(src+1, dest+1);
}

// Make tube k the same color.  If there are k+1 tubes in play,
// there should be exactly k colors still in play and 3*k balls.
void solve(int k)
{
  // first make sure each tube has at least one ball.  If there
  // is any that is empty, there can be at most one and all others
  // are completely full
  set<int> has_room;
  for (int i = 0; i <= k; i++) {
    if (tsize[i] < 3) has_room.insert(i);
  }

  // if there are only two tubes, then it's easy
  if (k == 1) {
    while (tsize[0] > 0) {
      do_move(0, 1, has_room);
    }
    return;
  }

  // make tube k to have exactly one element
  if (tsize[k] == 0) {
    do_move(0, k, has_room);
  }
  while (tsize[k] > 1) {
    int d = *has_room.begin();
    assert(d != k);
    do_move(k, d, has_room);
  }

  int color = tube[k][0];
  
  // now look for the 2 balls of the same color
  while (tsize[k] < 3) {
    int si = -1, sj = -1;
    for (int i = 0; i < k && si < 0; i++) {
      for (int j = tsize[i]-1; j >= 0 && si < 0; j--) {
	if (tube[i][j] == color) {
	  si = i;
	  sj = j;
	}
      }
    }
    assert(si >= 0 && sj >= 0);
    
    // clear things on top
    while (sj < tsize[si]-1) {
      int d = -1;
      for (auto x : has_room) {
	if (x != si) {
	  d = x;
	  break;
	}
      }
      assert(d >= 0);
      if (d < k) {
	do_move(si, d, has_room);
      } else {
	assert(tsize[si] == 2 && tsize[k] == 1);
	do_move(si, k, has_room);
	do_move(si, k, has_room);
	for (int i = 0; i < k; i++) {
	  if (tsize[i] == 3) {
	    do_move(i, si, has_room);
	    do_move(k, i, has_room);
	    do_move(k, si, has_room);
	    si = i;
	    sj = 2;
	    break;
	  }
	}
      }
    }

    // just move it
    assert(sj == tsize[si]-1);
    do_move(si, k, has_room);
  }
}

int main()
{
  cin >> n;
  for (int i = 0; i < n+1; i++) {
    for (int j = 0; j < 3; j++) {
      cin >> tube[i][j];
      if (tube[i][j]) tsize[i]++;
    }
  }

  for (int k = n; k >= 1; k--) {
    solve(k);
  }

  cout << moves.size() << endl;
  for (auto [a, b] : moves) {
    cout << a << ' ' << b << endl;
  }
  
  return 0;
}
