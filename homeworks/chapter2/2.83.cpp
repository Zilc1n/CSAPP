#include <cassert>
#include <iostream>



int main() {
    float x = 1.2;
    x = (int)x >> 1;
    std::cout << x << '\n';
    return 0;
}