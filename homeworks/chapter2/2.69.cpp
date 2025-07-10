#include <cassert>
unsigned rotate_left(unsigned x, int n) {
    unsigned r = x >> (32 - n);
    unsigned l = x << n;
    return l | r;
}

int main() {
    int x = 0x12345678;
    assert(rotate_left(x, 4) == 0x23456781);
    assert(rotate_left(x, 20) == 0x67812345);
    return 0;
}