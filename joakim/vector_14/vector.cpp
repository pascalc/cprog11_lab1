#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdexcept>
#include "vector_14.h"

using namespace std;

// Default constructor
Vector::Vector() {
	capacity = 0;
	size = 0;
	array = 0;
};

// Constructor creates Vector which size elements to be hold
Vector::Vector(size_t size) {
	// size = argument passed. capacity = size of "type of argument" * size
	this->size = size;
	capacity = size * sizeof(unsigned int);
	array = new unsigned int[size];
	
	// Set all values to zero
	initiate(array);
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
//Vector::~Vector() { delete [] array; }

/** FUNCTION DECLARATIONS **/

const unsigned int Vector::operator[](unsigned int index) const {
    if(index >= size)
		throw std::out_of_range ("Trying to access index out of rage");    	
    return this->array[index];
}

unsigned int& Vector::operator[](unsigned int index) {
    if(index >= size)
    	throw std::out_of_range ("Trying to access index out of rage");
    	
    return this->array[index];
}

Vector& Vector::operator=(const Vector &vector) {
	
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

/**
	Set all the values in an array to zero
	arg: starting point of a array a 
*/
void Vector::initiate(unsigned int * array) {
	for(unsigned int i = 0; i < size; i++)
		*(array++) = 0; // equivalent with array[i] = 0;
}