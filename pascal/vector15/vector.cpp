#include <iostream>
#include "vector.h"
// #include <vector>
using namespace std;

int main(){
	Vector<int> ivec;
        for(int i = 0; i < 10; i++)
            ivec.insert(9-i, i);
	return 0;
}