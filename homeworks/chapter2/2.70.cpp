#include <cassert>
int fits_bits(int x, int n) {
    int mask = (1 << n) - 1;
    return !(x & ~mask);
}

int main() {
    assert(!fits_bits(2, 1));
    assert(fits_bits(2, 2));
    return 0;
}