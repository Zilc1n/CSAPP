#include <cassert>

typedef unsigned float_bits;

// compute |f|. If is NaN, then return f.
float_bits float_absval(float_bits f) {
    unsigned exp = (f >> 23) & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    int is_NaN = (exp == 0xff) and (!frac);
    return (is_NaN ? f : (0 << 31 | exp << 23 | frac));
}

int main() {
    
    return 0;
}