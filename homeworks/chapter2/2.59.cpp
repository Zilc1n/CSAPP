#include <iostream>

#define mask 0xff

int work(int x, int y) {
    return (y & ~mask) | (x & mask);
}

int main() {
    int x = 0x89abcdef, y = 0x76543210;
    std::cout << std::hex << work(x, y) << '\n';
    return 0;
}