#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "vector_15.h"

// Default constructor
Vector::Vector() {
	capacity = 0;
	size = 0;
	array = 0;
};

// Constructor creates Vector which size elements to be hold
Vector::Vector(size_t size) {
	// size = argument passed. capacity = size of "type of argument" * size
	size = size;
	capacity = size * sizeof(unsigned int);
	array = new unsigned int[size];
	
	// Set all values to zero
	initiate(array);
}

Vector::Vector(size_t size, const T &val) {
	// size = argument passed. capacity = size of "type of argument" * size
	size = size;
	capacity = size * sizeof(unsigned int);
	array = new unsigned int[size];
	
	// Set all values to zero
	initiate(array, val);	
}

// Copy constructor
Vector::Vector(const Vector &v) {
	unsigned int new_size = v.size;
	unsigned int new_capacity = v.capacity;
	unsigned int * buffer = new unsigned int[new_size];
	
	memcpy(buffer, v.array, new_capacity);

	// memory secured??
}

// Delete constructor
Vector::~Vector() {
	delete [] array;
}

/** FUNCTION DECLARATIONS **/

unsigned int Vector::operator[](unsigned int index) {
    if(index >= size) {
    	//std::out_of_range;
    	return 0;	// Error 
    }
    	
    return array[index];
}

Vector & Vector::operator=(const Vector & vector) {
	
	// allocate memory for new vector and copy elements from old vector
	unsigned int * new_array = new unsigned int[vector.size];
	memcpy(vector.array, new_array, vector.capacity);

	// free memory
	delete [] array;

	// copy new array to old
	array = new_array;
	size = vector.size;

	return * this;
}

void pusb_back(const T &elem) {
	// Check if enough capacity
	if(size >= capacity + sizeof(elem)) {
		array[size++] = elem; 
	} else {
		// Resize to make it fit (potentially add space for future use)
		//resize();
		array[size++] = elem;
	}
}

void insert(size_t i, const T &elem) {
	// Check if enough capacity else resize
	if(size <= capacity ) {
		// resize();
	}

	if(i == size) {
		push_back(elem);
		return;
	}
	
	// {0,1,2,3,4,6,7,8,9} insert(6, 5); -> move 6,7,8,9 one step right. insert 5.
	// Copy everything from i to i+1 (zero or one index??)
	//memcpy(vector.array + sizeof(elem), vector.array, );
	// insert new element at i

	}

}

void erase(size_t i) {
	array[i] = 0;

	// Copy all elements right of i to i-1
}

void clear() {
	memset(array, 0, size);
}

size_t size() {
	return size;
}

void resize() {
	capacity = 2*capacity;
	T * new_array = new T[capacity];

	memcpy(new_array, array, size);

	delete [] array;

	array = new_array();
}

void Vector::initiate(unsigned int * array, const T &val = T()) {
	for(unsigned int i = 0; i < size; i++) {
		*(array++) = *val; // equivalent with array[i] = *val;	
	}
}