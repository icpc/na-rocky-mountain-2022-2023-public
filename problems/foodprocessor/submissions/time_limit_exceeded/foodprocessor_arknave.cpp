#pragma GCC optimize("Ofast")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int32_t s, t, n;
    std::cin >> s >> t >> n;

    std::vector<std::array<int32_t, 2>> blades(n);
    for (auto i = 0; i < n; ++i) {
        std::cin >> blades[i][0] >> blades[i][1];
    }

    constexpr int32_t INF = 1e9;
    double ans = 0;
    while (s > t) {
        int32_t goal = t;
        int32_t fastest = INF;
        for (auto [m, h] : blades) {
            if (goal < m && m < s) {
                goal = m;
            }
            if (s <= m && h < fastest) {
                fastest = h;
            }
        }

        if (fastest == INF) break;

        ans += fastest * (std::log2(s) - std::log2(goal));
        s = goal;
    }

    if (s != t) {
        ans = -1;
    }

    std::cout << ans << '\n';
}
