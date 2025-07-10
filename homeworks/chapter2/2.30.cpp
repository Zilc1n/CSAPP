#include <iostream>
#include <climits>

/*Determine whether arguments can be added without overflow*/
int tadd_ok(int x, int y) {
    int ans = x + y;
    return !((x > 0 and y > 0 and ans <= 0) or (x < 0 and y < 0 and ans >= 0));
}

int main() {
    int x = INT_MAX, y = INT_MAX;
    std::cout << "x is " << x << " and y is " << y << ' ' << tadd_ok(x, y) << '\n';
    x = 1, y = 1;
    std::cout << "x is " << x << " and y is " << y << ' ' << tadd_ok(x, y) << '\n';
    return 0;
}