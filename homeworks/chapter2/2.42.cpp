#include <cstdint>
#include <iostream>
#include <climits>

int32_t div16(int32_t div) {
    int32_t bias = (div >> 31) & 0xf;
    return (div + bias) >> 4;
}

int main() {
    int x;
    std::cin >> x;
    std::cout << x << ' ' << div16(x) << " 111\n";
    return 0;
}