const int mask = 0xffffffff;

int main() {
    auto check = [&](int x) {
        return (!~x) or (!x) or ~(~x | ~0xff) or ((x >> ((sizeof(int) - 1) << 3)) & 0xff);
    };
    return 0;
}