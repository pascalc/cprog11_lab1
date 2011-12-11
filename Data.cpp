#include <iostream>
#include <stdlib.h>
using namespace std;

struct Data {
    int x, y, z;
};  

Data ** foo(Data ** v, int x) {
    for (int i = 0; i < x; i++) {
        //if (v[i] != 0) 
        	v[i] = new Data;
        //cout << "*&v[i]: " << *&v[i] << " -> i = " << i << " v[i] = " << v[i] << endl;
    }
    return v;
}

int main () {
    const int size = 5;
    Data ** v = new Data * [size];
    //foo(v, size);
    Data ** p = foo(v, size);
    delete [] *p;
}
