#include <cassert>
#include <climits>
#include <cstdio> // Added for printf

typedef unsigned float_bits;

// compute (int) f.
// if conversion causes overflow or f is NaN, return 0x80000000
int float_f2i(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = (f >> 23) & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    if (exp == 0xFF) {
        return INT_MIN;
    }
    
    if (exp == 0) {
        return 0;
    }

    int E = (int)exp - 127;
    if (E < 0) {
        return 0;
    }
    unsigned long long mantissa = frac | (1ULL << 23);
    
    if (E > 23) {
        mantissa <<= (E - 23);
    } else {
        mantissa >>= (23 - E);
    }

    if (!sign) {
        if (mantissa > (unsigned)INT_MAX) {
            return INT_MIN;
        }
        return (int)mantissa;
    } else {
        if (mantissa > (unsigned)INT_MAX + 1U) {
            return INT_MIN;
        }
        return -(int)mantissa;
    }
}

int main() {
    // 1. NaN and Infinity cases: Should return 0x80000000 (INT_MIN)
    assert(float_f2i(0x7FC00000) == INT_MIN); // QNaN
    assert(float_f2i(0x7F800001) == INT_MIN); // SNaN
    assert(float_f2i(0xFFC00000) == INT_MIN); // Negative QNaN
    assert(float_f2i(0x7F800000) == INT_MIN); // +Infinity
    assert(float_f2i(0xFF800000) == INT_MIN); // -Infinity

    // 2. Overflow cases (values too large for int): Should return 0x80000000 (INT_MIN)
    assert(float_f2i(0x4F000000) == INT_MIN); // 2^31, overflows
    assert(float_f2i(0x4F000001) == INT_MIN);
    assert(float_f2i(0x4F7FFFFF) == INT_MIN);
    assert(float_f2i(0x4F800000) == INT_MIN);
    assert(float_f2i(0xCF000001) == INT_MIN);
    assert(float_f2i(0xCF7FFFFF) == INT_MIN);
    assert(float_f2i(0xCF800000) == INT_MIN);

    // 3. Zero cases: Should convert to 0
    assert(float_f2i(0x00000000) == 0); // +0.0
    assert(float_f2i(0x80000000) == 0); // -0.0

    // 4. Values between -1 and 1 (exclusive): Should convert to 0 (truncation towards zero)
    assert(float_f2i(0x3F7FFFFF) == 0); // 0.999...f -> 0
    assert(float_f2i(0xBF7FFFFF) == 0); // -0.999...f -> 0
    assert(float_f2i(0x3F000000) == 0); // 0.5f -> 0
    assert(float_f2i(0xBF000000) == 0); // -0.5f -> 0
    assert(float_f2i(0x00800000) == 0);
    assert(float_f2i(0x00000001) == 0);
    assert(float_f2i(0x80800000) == 0);
    assert(float_f2i(0x80000001) == 0);

    // 5. Positive normalized numbers within int range
    assert(float_f2i(0x3F800000) == 1);       // 1.0f -> 1
    assert(float_f2i(0x40000000) == 2);       // 2.0f -> 2
    assert(float_f2i(0x40400000) == 3);       // 3.0f -> 3
    assert(float_f2i(0x404CCCCC) == 3);       // ~3.2f -> 3 (truncates)
    assert(float_f2i(0x405FFFFF) == 3);       // ~3.999f -> 3 (truncates)
    assert(float_f2i(0x47800000) == 65536);   // 65536.0f (2^16)

    // The float 0x4effffff represents the exact integer 2147483520.
    // It does NOT represent INT_MAX. A correct float_f2i function should return its actual value.
    assert(float_f2i(0x4effffff) == 2147483520);

    // 6. Negative normalized numbers within int range
    assert(float_f2i(0xBF800000) == -1);      // -1.0f -> -1
    assert(float_f2i(0xC0000000) == -2);      // -2.0f -> -2
    assert(float_f2i(0xC0400000) == -3);      // -3.0f -> -3
    assert(float_f2i(0xC04CCCCC) == -3);      // ~-3.2f -> -3 (truncates)
    assert(float_f2i(0xC05FFFFF) == -3);      // ~-3.999f -> -3 (truncates)
    assert(float_f2i(0xC7800000) == -65536);  // -65536.0f (-2^16)

    // Smallest negative integer that fits in int: INT_MIN (-2^31)
    // The float representation of -2147483648.0f is 0xCF000000
    assert(float_f2i(0xCF000000) == INT_MIN);
    return 0;
}