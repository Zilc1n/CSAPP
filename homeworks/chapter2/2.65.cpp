/*  Return 1 when x contains an odd number of 1s; 0 otherwise
    Asume w = 32  */
#include <iostream>
int odd_ones(unsigned x) {
    x ^= (x >> 16);
    x ^= (x >> 8);
    x ^= (x >> 4);
    x ^= (x >> 2);
    x ^= (x >> 1);
    return x & 1;
}

int main() {
    unsigned x;
    while (std::cin >> x) {
        if (x == -1) break;
        std::cout << odd_ones(x) << '\n';
    }
    return 0;
}