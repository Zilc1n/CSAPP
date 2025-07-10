#include <cassert>

unsigned f2u(float x) {
    return *(unsigned *)&x;
}

int float_le(float x, float y) {
    unsigned ux = f2u(x), uy = f2u(y);
    unsigned exp_x = (ux >> 23) & 0xFF, exp_y = (uy >> 23) & 0xFF;
    unsigned frac_x = ux & 0x7FFFFF, frac_y = uy & 0x7FFFFF;
    if ((exp_x == 0xFF && frac_x) || (exp_y == 0xFF && frac_y)) return 0;
    if (ux == uy) return 1;
    unsigned sx = ux >> 31, sy = uy >> 31;
    if (sx != sy) return sx > sy;
    return sx ? ux > uy : ux < uy;
}

int main() {
    assert(float_le(-0, +0));
    assert(float_le(+0, -0));
    assert(float_le(0, 3));
    assert(float_le(-4, -0));
    assert(float_le(-4, 4));
    return 0;
}