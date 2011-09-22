#include <iostream>
#include <stdexcept>

class Vector {
private:
	// Internal 'backbone' array
	int * array;
	size_t capacity;

public:
	// TODO: Copy constructor, assignment operator, setter: v[3] = 2;

	// Standard constructor
	Vector(size_t initial_size) {
		std::cout << "Standard constructor" << std::endl;
		capacity = initial_size;
		array = new int [initial_size];
	}

	// Copy constuctor
	Vector(const Vector& copy) {
		// Allocate a new array of the appropriate capacity and populate it
		std::cout << "Copy constructor" << std::endl;
		array = new int [copy.size()];
		for (int i = 0; i < copy.size(); i++) {
			array[i] = copy[i];
		}
	}

	// Deconstructor
	~Vector() {
		std::cout << "Destructor" << std::endl;
		delete [] array;
	}

	// Return the capacity of this Vector
	size_t size() const {
		return capacity;
	}

	// Read operator
	// vector[3] returns the int at index 3
 	int operator[](int index) const {
 		if (index >= capacity || index < 0) {
 			throw std::out_of_range("Out of range!");
 		}
 		return array[index];	
	}

	// Assignment operator
	Vector& operator=(const Vector& rhs) {
		std::cout << "= operator" << std::endl;
		// Trivial case, v1 = v1
		// if (this == rhs) {
		// 	return *this;
		// }
		
		// Otherwise copy the rhs array into our own
		capacity = rhs.size();
		array = new int [capacity];
		for (int i = 0; i < capacity; i++) {
			array[i] = rhs[i];
		}
		return *this;
	}
};

int main(){
	int x = 3;
	const int & xref = x;
	std::cout << &x << std::endl;
	std::cout << &xref << std::endl;
	return 0;
}