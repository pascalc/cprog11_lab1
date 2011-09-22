#include <iostream>

class Vector {
private:
	// Internal 'backbone' array
	int * array;

public:

	// Standard constructor
	Vector(size_t size) {
		array = new int [size];
	}

	// Deconstructor
	~Vector() {
		delete [] array;
	}

	// vector[3] returns the int at index 3
 	int operator[](int index) const {
		return array[index];
	}
};

int main(){
	Vector v(10);
	std::cout << "v[2] = " << v[2] << std::endl;
	std::cout << "sizeof(v) = " << sizeof(v) << std::endl;
	return 0;
}