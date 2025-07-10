#include <cassert>

int any_odd_one(unsigned x) {
    return (0xAAAAAAAA & x);
}

int main() {
    assert(any_odd_one(0x2));
    assert(!any_odd_one(0x4));
    return 0;
}