#include <cassert>
int lower_one_mask(int n) {
    int t = 1 << (n - 1);
    t <<= 1;
    return t - 1;
}

int main() {
    assert(lower_one_mask(6) == 0x3f);
    assert(lower_one_mask(17) == 0x1ffff);
    assert(lower_one_mask(32) == 0xffffffff);
    return 0;
}