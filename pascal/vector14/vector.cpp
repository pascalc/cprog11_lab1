#include <iostream>
#include <stdexcept>

#include "vector.h"
	// Default constructor
	Vector::Vector() {
		capacity = 0;
		array = new unsigned int [0];
	}

	// Standard constructor
	Vector::Vector(size_t initial_size) {
		capacity = initial_size;
		array = new unsigned int [initial_size];
		for (size_t i = 0; i < capacity; i++){
			array[i] = 0;
		}
	}

	// Copy constuctor
	Vector::Vector(const Vector& copy) {
		// Allocate a new array of the appropriate capacity and populate it
		capacity = copy.size();
		array = new unsigned int [capacity];
		for (size_t i = 0; i < capacity; i++) {
			array[i] = copy[i];
		}
	}

	// Deconstructor
	Vector::~Vector() {
		delete [] array;
	}

	// Return the capacity of this Vector
	size_t Vector::size() const {
		return capacity;
	}

	// Read operator
	const unsigned int& Vector::operator[](unsigned int index) const{
		if (index >= capacity || index < 0) {
			throw std::out_of_range("Out of range!");
		}
		return array[index];	
	}
	// Write operator
	unsigned int& Vector::operator[](unsigned int index) {
		if (index >= capacity || index < 0) {
			throw std::out_of_range("Out of range!");
		}
		return array[index];	
	}

	// Assignment operator
	Vector& Vector::operator=(const Vector& rhs) {
		// Trivial case, v1 = v1
		if (this == &rhs) {
			return *this;
		}
		
		// Otherwise copy the rhs array into our own
		capacity = rhs.size();
		array = new unsigned int [capacity];
		for (size_t i = 0; i < capacity; i++) {
			array[i] = rhs[i];
		}
		return *this;
	}