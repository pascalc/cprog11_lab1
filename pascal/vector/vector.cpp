#include <iostream>

class Vector {
private:
	// Internal 'backbone' array
	int * array;

public:

	// Standard constructor
	Vector(int size) {
		array = new int [size];
	}

	// Deconstructor
	~Vector() {
		delete [] array;
	}

	// vector[3] returns the int at index 3
	int operator[](int index) {
		return array[index];
	}
};

int main(){
	Vector * v = new Vector(100);
	std::cout << "v[2] = " << (*v)[2] << std::endl;
	delete v;
	return 0;
}