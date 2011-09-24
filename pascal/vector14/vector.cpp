#include <iostream>
#include <stdexcept>

//#include "vector.h"

class Vector {
private:
	// Internal 'backbone' array
	int * array;
	unsigned int capacity;

public:
	struct array_proxy {
		int & ref;
		array_proxy(int & r) : ref(r) {}
		void operator = (int value) {
			ref = value;
		}
		operator int() const{
			return ref;
		}
		// Prefix ++
		int operator ++ () {
			return ++ref;
		}
		// Postfix ++
		int operator ++ (int i) {
			return ref++;
		}
	};

	// Standard constructor
	explicit Vector(unsigned int initial_size) {
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
	unsigned int size() const {
		return capacity;
	}

	// Read operator
	int operator[](unsigned int index) const{
		if (index >= capacity || index < 0) {
			throw std::out_of_range("Out of range!");
		}
		return array[index];	
	}
	// Write via array_proxy
	array_proxy operator[](unsigned int index) {
		if (index >= capacity || index < 0) {
			throw std::out_of_range("Out of range!");
		}
		return array_proxy(array[index]);	
	}

	// Assignment operator
	Vector& operator=(const Vector& rhs) {
		// Trivial case, v1 = v1
		// if (this == rhs) {
		// 	return *this;
		// }
		
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
	unsigned int x = 5;
	Vector v = Vector(x);
	Vector w = v;
	for(int i = 0; i < 10; i++) {
		std::cout << v[0]++ << std::endl;	
	}
	std::cout << w[0] << std::endl;		
	return 0;
}