#include <iostream>
#include "vector.h"
// #include <vector>
using namespace std;

int main(){
	Vector<double> v = Vector<double>();
	v.push_back(2.71);
	v.push_back(3.14);
	v.insert(1,9.81);
	v.push_back(13.37);
	v.push_back(42);
	v.sort(false);
	for(unsigned int i = 0; i < v.size(); i++)
		cout << v[i] << endl;
	return 0;
}