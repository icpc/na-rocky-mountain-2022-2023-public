#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int S, T, N;
  while (cin >> S >> T >> N) {
    vector<pair<int, int>> B(N);
    for (auto& [H, M] : B) cin >> M >> H;
    B.push_back({0, 0});
    sort(B.begin(), B.end());
    for (int i = 1; i < B.size(); i++) B[i].second = max(B[i].second, B[i-1].second);
    if (B.back().second < S) { cout << -1 << endl; continue; }
    double ret = 0.0;
    for (int i = B.size()-1; S > T; i--) {
      int target = min(S, max(B[i-1].second, T));
      ret += (log(S)-log(target))/log(2) * B[i].first;
      S = target;
    }
    cout << setprecision(9) << ret << endl;
  }
}
