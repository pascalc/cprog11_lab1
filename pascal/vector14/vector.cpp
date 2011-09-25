#include <iostream>
#include <stdexcept>

//#include "vector.h"

class Vector {
private:
	// Internal 'backbone' array
	int * array;
	size_t capacity;

public:
	// Standard constructor
	explicit Vector(size_t initial_size) {
		capacity = initial_size;
		array = new int [initial_size];
	}

	// Copy constuctor
	Vector(const Vector& copy) {
		// Allocate a new array of the appropriate capacity and populate it
		capacity = copy.size();
		array = new int [capacity];
		for (unsigned int i = 0; i < capacity; i++) {
			array[i] = copy[i];
		}
	}

	// Deconstructor
	~Vector() {
		delete [] array;
	}

	// Return the capacity of this Vector
	size_t size() const {
		return capacity;
	}

	// Read operator
	const int& operator[](unsigned int index) const{
		if (index > capacity-1 || index < 0) {
			throw std::out_of_range("Out of range!");
		}
		return array[index];	
	}
	// Write operator
	int& operator[](unsigned int index) {
		if (index > capacity-1 || index < 0) {
			throw std::out_of_range("Out of range!");
		}
		return array[index];	
	}

	// Assignment operator
	Vector& operator=(const Vector& rhs) {
		// Trivial case, v1 = v1
		if (this == &rhs) {
			return *this;
		}
		
		// Otherwise copy the rhs array into our own
		capacity = rhs.size();
		array = new int [capacity];
		for (int unsigned i = 0; i < capacity; i++) {
			array[i] = rhs[i];
		}
		return *this;
	}
};

int main(){
	Vector v = Vector(10);
	Vector w = v;
	for(int i = 0; i < 10; i++) {
		std::cout << v[0]++ << std::endl;	
	}
	std::cout << w[0] << std::endl;		
	return 0;
}