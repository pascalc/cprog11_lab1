#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdexcept>
#include <algorithm>
#include "vector.h"

/** Vector 1.5 **/

// Default constructor
template <class T>
Vector<T>::Vector() {
	capacity = 0;
	size = 0;
	array = 0;
};

// Constructor creates Vector which size elements to be hold
template <class T>
Vector<T>::Vector(size_t size) {
	this->size = size;
	capacity = size;
	array = new T[capacity];
	
	// Set all values to zero
	initiate(array);
}
template <class T>
Vector<T>::Vector(size_t size, const T &val) {
	// size = argument passed. capacity = size of "type of argument" * size
	this->size = size;
	capacity = size;
	array = new T[capacity];
	
	// Set all values to zero
	initiate(array, val);	
}

// Copy constructor
template <class T>
Vector<T>::Vector(const Vector<T> &v) {
	size = v.size;
	capacity = v.capacity;
	array = new T[capacity];
	
	memcpy(array, v.array, capacity);

	// memory secured??
}

/** FUNCTION DECLARATIONS **/

template <class T>
const unsigned int Vector<T>::operator[](unsigned int index) const {
    if(index >= size)
		throw std::out_of_range ("Trying to access index out of range");    	
    return this->array[index];
}

template <class T>
unsigned int& Vector<T>::operator[](unsigned int index) {
    if(index >= size)
    	throw std::out_of_range ("Trying to access index out of range");
    	
    return this->array[index];
}

template <class T>
Vector<T> & Vector<T>::operator=(const Vector<T> & vector) {
	
	// allocate memory for new vector and copy elements from old vector
	T *new_array = new T[vector.capacity];
	memcpy(new_array, vector.array, vector.capacity);

	// free memory
	delete [] array;

	// assign new data
	array = new_array;
	size = vector.size;
	capacity = vector.capacity;

	return *this;
}

template <class T>
void Vector<T>::push_back(const T &elem) {
	// Check if enough capacity
	if(size < capacity) 
		resize();
	
	array[size++] = elem; 
}

template <class T>
void Vector<T>::insert(size_t i, const T &elem) {
	if(i > size) throw std::out_of_range("Trying to access index out of range");
	
	// If i is last index this functions equals push_back
	if(i == size) {
		push_back(elem);
		return;
	}

	// Check if enough capacity else resize
	if(size < capacity ) resize();
	
	// Copy everything from i to i+1 (zero or one index??)
	memcpy(i+1, i, size-1);
	array[i] = elem;

	size++;
}

template <class T>
void Vector<T>::erase(size_t i) {
	array[i] = 0;
	// Copy all elements right of i to i-1
	memcpy(i, i+1, size-1);
	size--;
}

template <class T>
void Vector<T>::clear() { memset(array, 0, size); size = 0; }

template <class T>
const size_t Vector<T>::size() const { return size; }

template <class T>
void Vector<T>::resize() {
	capacity = capacity + ceil(size/2);
	T * new_array = new T[capacity];
	memcpy(new_array, array, size);
	delete [] array;
	array = new_array;
}

template <class T>
void Vector<T>::sort(bool ascending = true) {
	sort(array, array+size);

	if(!ascending);
}

/** PRIVATE FUNCTIONS **/
template <class T>
void Vector<T>::initiate(T *array, const T &val = 0) {
	for(unsigned int i = 0; i < size; i++) {
		*(array++) = *val; // equivalent with array[i] = *val;

	}
}