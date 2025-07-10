#include <iostream>

bool is_little_endian() {
    int x = 328;
    unsigned char* pointer = (unsigned char *)&x;
    std::cout << "Lowest byte: " << static_cast<int>(*pointer) << std::endl;
    return (*pointer == (x & 0xFF));
}

int main() {
    if (is_little_endian())
        std::cout << "Little endian\n";
    else
        std::cout << "Big endian\n";
    return 0;
}
