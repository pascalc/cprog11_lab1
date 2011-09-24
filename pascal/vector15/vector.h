#include <iostream>
#include <stdexcept>

template <class T>
class Vector {
private:
	// Internal 'backbone' array
	T * array;
	unsigned int capacity;

public:
	struct array_proxy {
		T & ref;
		array_proxy(T & r) : ref(r) {}
		void operator = (T value) {
			ref = value;
		}
		operator T() const{
			return ref;
		}
		// Prefix ++
		// int operator ++ () {
		// 	return ++ref;
		// }
		// // Postfix ++
		// int operator ++ (T i) {
		// 	return ref++;
		// }
	};

	// Standard constructor
	explicit Vector<T>(unsigned int initial_size) {
		capacity = initial_size;
		array = new T [initial_size];
	}

	// Copy constuctor
	Vector<T>(const Vector& copy) {
		// Allocate a new array of the appropriate capacity and populate it
		capacity = copy.size();
		array = new T [capacity];
		for (unsigned int i = 0; i < capacity; i++) {
			array[i] = copy[i];
		}
	}

	// Deconstructor
	~Vector<T>() {
		delete [] array;
	}

	// Return the capacity of this Vector
	unsigned int size() const {
		return capacity;
	}

	// Read operator
	T operator[](unsigned int index) const{
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
	Vector<T>& operator=(const Vector<T>& rhs) {
		// Trivial case, v1 = v1
		// if (this == rhs) {
		// 	return *this;
		// }
		
		// Otherwise copy the rhs array into our own
		capacity = rhs.size();
		array = new T [capacity];
		for (int unsigned i = 0; i < capacity; i++) {
			array[i] = rhs[i];
		}
		return *this;
	}
};