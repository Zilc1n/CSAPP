#include <cassert>
#include <climits>

int A(int k) {
    return -1 << k;
}

int B(int k, int j) {
    // return (-1 << j) & ~(INT_MIN >> (32 - k - j - 1));
    return ~A(k) << j;
}

int main() {
    assert(A(8) == 0xFFFFFF00);
    assert(B(16, 8) == 0x00FFFF00);
    return 0;
}