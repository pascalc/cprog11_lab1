#include <iostream>
using namespace std;

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

    cout << x << " upph�jt till " << y << " �r " << res << endl;

    float z = 0.29;
    int w = (int) (z * x * x);
    if (z * x * x == 29)
        cout << z << "*" << x * x << " �r 29" << endl;
    else
        cout << z << "*" << x * x << " �r inte 29" << endl;
}
