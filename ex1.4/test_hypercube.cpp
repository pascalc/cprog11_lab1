#include <iostream>
#include "hypercube.h"

int main() {
	std::cout << "\n Testing hypercube class \n";
	Hypercube<3> n(7); // kub med 7*7*7 element
	Hypercube<6> m(5); // sex dimensioner, 5*5*...*5 element
	m[1][3][2][1][4][0] = 7;
	
	Hypercube<3> t(5);
	t = m[1][3][2]; // tilldela med del av m
	t[1][4][0] = 2; // ändra t, ändra inte m
	std::cout << m[1][3][2][1][4][0] << std::endl; // 7
	std::cout << t[1][4][0] << std::endl; // 2
	
	return 0;
}