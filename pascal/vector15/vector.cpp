#include <iostream>
#include "vector.h"
// #include <vector>
using namespace std;

int main(){
	Vector<double> v = Vector<double>(1);
	v.clear();
	v.insert(0,1);
	for(unsigned int i = 0; i < v.size(); i++)
		cout << v[i] << endl;
	return 0;
}