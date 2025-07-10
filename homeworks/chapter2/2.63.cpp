
#include <iostream>
unsigned srl(unsigned x, int k) {
    int xsra = (int)x >> k;
    unsigned mask = ~((~0U) << (32 - k));
    return xsra & mask;
}

int sra(int x, int k) {
    int xsrl = (unsigned) x >> k;
    int sign = x >> 31;
    unsigned mask = ~((~0U) >> k);
    std::cout << sign << '\n';
    return xsrl | (mask & (sign << (32 - k)));
}

int main() {
    std::cout << sra(-4, 0) << '\n';
    return 0;
}