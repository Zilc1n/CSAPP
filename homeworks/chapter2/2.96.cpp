#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>

typedef unsigned float_bits;

// compute (int) f.
// if conversion causes overflow or f is NaN, return 0x80000000
int float_f2i(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = (f >> 23) & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    if (exp == 0xff or exp >= 0x20) {
        return INT_MIN;
    }

    unsigned s = frac >> std::max(23 - (int)exp, 0);
    return (-sign * (s << exp));
}

int main() {
    // 1. NaN and Infinity cases: Should return 0x80000000 (INT_MIN)
    assert(float_f2i(0x7FC00000) == INT_MIN); // QNaN
    assert(float_f2i(0x7F800001) == INT_MIN); // SNaN
    assert(float_f2i(0xFFC00000) == INT_MIN); // Negative QNaN
    assert(float_f2i(0x7F800000) == INT_MIN); // +Infinity
    assert(float_f2i(0xFF800000) == INT_MIN); // -Infinity

    // 2. Overflow cases (values too large for int): Should return 0x80000000 (INT_MIN)
    // 2^31 (0x4F000000) is one more than INT_MAX (2^31 - 1), so it overflows for positive.
    assert(float_f2i(0x4F000000) == INT_MIN);
    // Values just above INT_MAX for positive floats
    assert(float_f2i(0x4F000001) == INT_MIN);
    assert(float_f2i(0x4F7FFFFF) == INT_MIN);
    assert(float_f2i(0x4F800000) == INT_MIN); // Largest positive float exponent before infinity

    // Values just below INT_MIN for negative floats (more negative than -2^31)
    // -2^31 - epsilon (e.g., -2147483649.0) -> overflows to INT_MIN.
    // For floats, the representation of -2^31 (INT_MIN) is 0xCF000000.
    // Anything more negative (like -2^31 - 1.0) would technically be 0xCF000001 in integer,
    // but in float representation, it's about 0xCF000001 for slightly more negative.
    // A value slightly more negative than INT_MIN (e.g., -2147483649.0)
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
    // Smallest normalized positive float (0x00800000, 1.0 * 2^-126) -> 0
    assert(float_f2i(0x00800000) == 0);
    // Smallest non-zero denormalized float (0x00000001) -> 0
    assert(float_f2i(0x00000001) == 0);
    // Corresponding negative values`
    assert(float_f2i(0x80800000) == 0);
    assert(float_f2i(0x80000001) == 0);

    // 5. Positive normalized numbers within int range
    assert(float_f2i(0x3F800000) == 1);     // 1.0f -> 1
    assert(float_f2i(0x40000000) == 2);     // 2.0f -> 2
    assert(float_f2i(0x40400000) == 3);     // 3.0f -> 3
    assert(float_f2i(0x404CCCCC) == 3);     // 3.1f -> 3 (truncates)
    assert(float_f2i(0x405FFFFF) == 3);     // 3.999...f -> 3 (truncates)
    assert(float_f2i(0x47E00000) == 65536); // 65536.0f (2^16) -> 65536
    // Largest positive integer that fits in int: INT_MAX (2^31 - 1)
    // The float representation of 2147483647.0f is 0x4EFF_FFFF
    assert(float_f2i(0x4effffff) == INT_MAX);

    // 6. Negative normalized numbers within int range
    assert(float_f2i(0xBF800000) == -1);     // -1.0f -> -1
    assert(float_f2i(0xC0000000) == -2);     // -2.0f -> -2
    assert(float_f2i(0xC0400000) == -3);     // -3.0f -> -3
    assert(float_f2i(0xC04CCCCC) == -3);     // -3.1f -> -3 (truncates towards zero)
    assert(float_f2i(0xC05FFFFF) == -3);     // -3.999...f -> -3 (truncates towards zero)
    assert(float_f2i(0xC7E00000) == -65536); // -65536.0f -> -65536
    // Smallest negative integer that fits in int: INT_MIN (-2^31)
    // The float representation of -2147483648.0f is 0xCF000000
    assert(float_f2i(0xCF000000) == INT_MIN);
    return 0;
}