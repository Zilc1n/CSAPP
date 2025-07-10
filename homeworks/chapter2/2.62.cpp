#include <cassert>
#include <iostream>
int int_shifts_are_arithmetic() {
    int num = -1;
    return !(num ^ (num >> 1));
}

int main() {
    assert(int_shifts_are_arithmetic());
    std::cout << "little_endian!\n";
    return 0;
}