#include <iostream>
#include <algorithm>
#include <queue>
#include <cmath>
#include <iomanip>

using namespace std;

struct Blade
{
  int M, H;
};

istream &operator>>(istream &is, Blade &b)
{
  return is >> b.M >> b.H;
}

bool cmp_size(const Blade &b1, const Blade &b2)
{
  return b1.M > b2.M;
}

// for priority queue
bool operator<(const Blade &b1, const Blade &b2)
{
  return b1.H > b2.H;
}
	      
const int MAX_N = 1000000;
int S, T, N;
Blade blade[MAX_N];

double perturb(double x, double eps)
{
  return x * (1 + eps);
}

int main()
{
  cin >> S >> T >> N;
  for (int i = 0; i < N; i++) {
    cin >> blade[i];
  }

  priority_queue<Blade> best_blade;

  sort(blade, blade+N, cmp_size);
  int bi = 0;
  int curr_size = S;
  double time = 0.0;
  while (curr_size > T) {
    // get all useable blades
    while (bi < N && blade[bi].M >= curr_size) {
      best_blade.push(blade[bi++]);
    }

    // can't do anything
    if (best_blade.size() == 0) break;
    
    // what can we get to next
    int next_blade_size = (bi < N) ? blade[bi].M : 0;
    int next_size = max(next_blade_size, T);
    time += (log2(curr_size) - log2(next_size)) * best_blade.top().H;
    best_blade.push(blade[bi++]);
    curr_size = next_size;
  }

  if (curr_size == T) {
    cout << setprecision(10) << perturb(time, -0.99e-5) << endl;
  } else {
    cout << setprecision(10) << -1 << endl;
  }
  
  
  return 0;
}
