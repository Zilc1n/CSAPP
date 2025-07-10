#include <cassert>
int threefourths(int x) {
    int x3 = x + (x << 1);  // x * 3
    int bias = (x3 >> 31) & 3;  // 如果是负数，加 bias=3
    return (x3 + bias) >> 2;
}

int main() {
    assert(threefourths(8) == 6);
    assert(threefourths(9) == 6);
    assert(threefourths(10) == 7);
    assert(threefourths(11) == 8);
    assert(threefourths(12) == 9);

    assert(threefourths(-8) == -6);
    assert(threefourths(-9) == -6);
    assert(threefourths(-10) == -7);
    assert(threefourths(-11) == -8);
    assert(threefourths(-12) == -9);
    return 0;
}