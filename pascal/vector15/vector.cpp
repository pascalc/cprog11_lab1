#include <iostream>
#include "vector.h"

int main(){
	Vector<double> v = Vector<double>(5);
	v[0] = 2.71;
	v[1] = 3.14;
	v[2] = 13.37;
	for(int i = 0; i < 3; i++)
		std::cout << v[i] << std::endl;
	return 0;
}