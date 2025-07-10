#include <cassert>
#include <cstdint>
int saturating_add(int x, int y) {
    int sum = x + y;
    int sig_mask = INT32_MIN;

    int pos_over = !(x & sig_mask) and !(y & sig_mask) and (sum & sig_mask);
    int neg_over = (x & sig_mask) and (y & sig_mask) and !(sum & sig_mask);

    (pos_over and (sum = INT32_MAX)) || (neg_over and (sum = sig_mask));

    return sum;
}

int main() {
    assert(INT32_MAX == saturating_add(INT32_MAX, 0x1234));
    assert(INT32_MIN == saturating_add(INT32_MIN, -0x1234));
    assert(0x11 + 0x22 == saturating_add(0x11, 0x22));
    return 0;
}