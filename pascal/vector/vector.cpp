#include <iostream>
#include <stdexcept>

class Vector {
private:
	// Internal 'backbone' array
	int * array;
	size_t capacity;

public:

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

	// Callback executed assigning to vector: v[2] = 3
	struct setter {
		// The address to write to
		int & ref;
		// Initialise which address to write to
		setter(int & i) : ref(i) {}
		// When assigned to, write value to addr
		void operator = (int value) {
			ref = value;
		}
	};
	// Write operator
	// vector[3] = 2 sets the int at index 3 to 2
 	// 	array_setter& operator[](int index) {
 	// 		if (index >= capacity || index < 0) {
 	// 			throw std::out_of_range("Out of range!");
 	// 		}
 	// 		return array_setter(array[index]);	
	// }
	void set(int index, int value) {
		//array[index] = value;
		setter a = setter(array[index]);
		a = value;
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
	Vector v = Vector(5);
	v.set(1,2);
	v.set(0,1337);
	std::cout << "v[0],v[1] = " << v[0] << "," << v[1] << std::endl;
	return 0;
}