#include <cassert>
#include <cstdint>
#include <iostream>

int main() {
    int32_t r, f;
    std::cin >> r >> f;

    f %= r + r;
    auto down = std::abs(r - f);
    auto up = std::min(r + r - f, f);
    assert(down != up);
    if (down < up) {
        std::cout << "down\n";
    } else {
        std::cout << "up\n";
    }
}
