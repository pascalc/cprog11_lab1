#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdexcept>
#include "vector.h"

using namespace std;

/** FUNCTION DECLARATIONS **/

const unsigned int Vector::operator[](unsigned int index) const {
    if(index >= my_size || index < 0)
		throw std::out_of_range ("\nTrying to access index out of range");    	
    return array[index];
}

unsigned int& Vector::operator[](unsigned int index) {
    if(index >= my_size || index < 0)
    	throw std::out_of_range ("\nTrying to access index out of range");
    	
    return array[index];
}

Vector& Vector::operator=(const Vector &v) {
	if(this == &v) 
		return *this;
	
	my_size = v.my_size;
	capacity = v.capacity;
	array = new unsigned int[capacity];
	
	memcpy(array, v.array, capacity * sizeof(unsigned int));
	return *this;
}

unsigned int Vector::size() const { return my_size; }