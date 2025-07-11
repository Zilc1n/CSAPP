#include <cassert>

typedef unsigned float_bits;

// compute f * 2. If is NaN, then return f.
float_bits float_twice(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = (f >> 23) & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    // NaN or infinity
    if (exp == 0xFF) {
        return f;
    }
    // Denormalized number or zero
    if (exp == 0) {
        frac = frac << 1;
        // If the shift causes the leading bit to be 1, normalize
        if (frac & 0x800000) {
            exp = 1;
            frac = frac & 0x7FFFFF; // 规格化后frac去掉最高位
        }
        return (sign << 31) | (exp << 23) | frac;
    }
    // Normalized number
    exp += 1;
    if (exp == 0xFF) { // overflow to infinity
        frac = 0;
    }
    return (sign << 31) | (exp << 23) | frac;
}

int main() {
    // 0x7FC00000: NaN, 应返回自身
    assert(float_twice(0x7FC00000) == 0x7FC00000);
    // 0x7F800000: +inf, 应返回自身
    assert(float_twice(0x7F800000) == 0x7F800000);
    // 0xFF800000: -inf, 应返回自身
    assert(float_twice(0xFF800000) == 0xFF800000);
    // 0x00000000: +0, 乘2还是0
    assert(float_twice(0x00000000) == 0x00000000);
    // 0x80000000: -0, 乘2还是-0
    assert(float_twice(0x80000000) == 0x80000000);
    // 0x00000001: 最小正非规格化数，左移一位
    assert(float_twice(0x00000001) == 0x00000002);
    // 0x00800000: 最小正规格化数，exp=1, frac=0，乘2后exp=2
    assert(float_twice(0x00800000) == 0x01000000);
    // 0x3F800000: 1.0f, 乘2后为2.0f
    assert(float_twice(0x3F800000) == 0x40000000);
    // 0xBF800000: -1.0f, 乘2后为-2.0f
    assert(float_twice(0xBF800000) == 0xC0000000);
    // 0x7F7FFFFF: 最大规格化正数，乘2后为+inf
    assert(float_twice(0x7F7FFFFF) == 0x7F800000);
    // 0xFF7FFFFF: 最大规格化负数，乘2后为-inf
    assert(float_twice(0xFF7FFFFF) == 0xFF800000);
    // 0x12345678: 随机数，人工计算结果
    assert(float_twice(0x12345678) == 0x12B45678);
    assert(float_twice(0x7fffff) == 16777214);
    return 0;
}