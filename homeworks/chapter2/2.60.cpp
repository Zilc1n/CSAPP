#include <cassert>
#include <iostream>
unsigned replace_byte(unsigned x, int i, unsigned char b) {
    if (i < 0) {
        std::cout << "error\n";
        return 0;
    }
    if (i > sizeof(unsigned) - 1) {
        std::cout << "too big i\n";
        return 0;
    }

    unsigned mask = ((unsigned) 0xff) << (i << 3);
    unsigned pos_mask = ((unsigned) b) << (i << 3);

    return (x & ~mask) | pos_mask;
}

int main() {
    unsigned rep_0 = replace_byte(0x12345678, 0, 0xAB);
    unsigned rep_3 = replace_byte(0x12345678, 3, 0xAB);

    assert(rep_0 == 0x123456AB);
    assert(rep_3 == 0xAB345678);
    std::cout << "ok!\n";
    return 0;
}