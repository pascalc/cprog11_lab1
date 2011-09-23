#include <iostream>
#include <stdexcept>

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
		std::cout << "Copy constructor" << std::endl;
		array = new int [copy.size()];
		for (unsigned int i = 0; i < copy.size(); i++) {
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
	int operator[](unsigned int index) const{
		if (index >= capacity || index < 0) {
			throw std::out_of_range("Out of range!");
		}
		return array[index];	
	}
	// Callback executed assigning to vector: v[2] = 3
	struct array_proxy {
		int & ref;
		array_proxy(int & r) : ref(r) {}
		void operator = (int value) {
			ref = value;
		}
		operator int() const{
			return ref;
		}
	};
	// Write via array_proxy
	array_proxy operator[](unsigned int index) {
		if (index >= capacity || index < 0) {
			throw std::out_of_range("Out of range!");
		}
		return array_proxy(array[index]);	
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
		for (int unsigned i = 0; i < capacity; i++) {
			array[i] = rhs[i];
		}
		return *this;
	}
};

int main(){
	Vector v = Vector(5);
	Vector w = v;
	for(int i = 0; i < 10; i++) {
		v[0] = v[0] + 1;
		std::cout << v[0] << std::endl;	
	}
	std::cout << w[0] << std::endl;		
	return 0;
}