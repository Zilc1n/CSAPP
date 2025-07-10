
#include <cassert>

typedef unsigned float_bits;

// compute f * 0.5. If is NaN, then return f.
float_bits float_half(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = (f >> 23) & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    if (exp == 0xFF) {
        return f; // NaN or infinity, return itself
    }

    if (exp == 0) {
        frac = frac >> 1;
        return (sign << 31) | (exp << 23) | frac;
    }

    if (exp == 1) {
        frac = (frac | 0x800000) >> 1;
        exp = 0;
    } else {
        exp -= 1;
    }
    return (sign << 31) | (exp << 23) | frac;
}

int main() {
    assert(float_half(0x7FC00000) == 0x7FC00000);
    assert(float_half(0x7F800001) == 0x7F800001);
    assert(float_half(0xFFC00000) == 0xFFC00000);
    assert(float_half(0x7F800000) == 0x7F800000);
    assert(float_half(0xFF800000) == 0xFF800000);
    assert(float_half(0x00000000) == 0x00000000);
    assert(float_half(0x80000000) == 0x80000000);
    assert(float_half(0x3F800000) == 0x3F000000);
    assert(float_half(0x40000000) == 0x3F800000);
    assert(float_half(0xBF800000) == 0xBF000000);
    assert(float_half(0x00800000) == 0x00400000);
    assert(float_half(0x80800000) == 0x80400000);
    assert(float_half(0x00000002) == 0x00000001);
    assert(float_half(0x00000001) == 0x00000000);
    assert(float_half(0x80000001) == 0x80000000);
    assert(float_half(0x00800001) == 0x00400000);
    assert(float_half(0x12345678) == 0x11B45678);
    assert(float_half(0x00800003) == 0x00400001);
    return 0;
}