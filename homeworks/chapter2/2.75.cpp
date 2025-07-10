#include <cassert>
#include <stdint.h>
int signed_high_prod(int x, int y) {
    int64_t mul = (int64_t)x * y;
    return mul >> 32;
}

unsigned unsigned_high_prod(unsigned x, unsigned y) {
    int signed_hp = signed_high_prod(x, y);
    // 补偿项
    unsigned x_sign = x >> 31;
    unsigned y_sign = y >> 31;
    return signed_hp + x_sign * y + y_sign * x;
}

unsigned another_unsigned_high_prod(unsigned x, unsigned y) {
    uint64_t mul = (uint64_t)x * y;
    return mul >> 32;
}

int main() {
    unsigned x = 0x12345678;
    unsigned y = 0xFFFFFFFF;

    assert(another_unsigned_high_prod(x, y) == unsigned_high_prod(x, y));
    return 0;
}