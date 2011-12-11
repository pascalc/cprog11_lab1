#include <iostream>

int powerof(int x, int y) {
    int res = 1;
    for (int i = 0; i < y; i++) {
        res *= x;
    }
    return res;
}

int main() {
    int x = 10;
    int y = 3;

    int res = powerof(x, y);

    std::cout << x << " upph�jt till " << y << " �r " << res << std::endl;

    float z = 0.29;
    int w = (int) (z * x * x);
    if (z * x * x == 29)
        std::cout << z << "*" << x * x << " �r 29" << std::endl;
    else
        std::cout << z << "*" << x * x << " �r inte 29" << std::endl;           
}
