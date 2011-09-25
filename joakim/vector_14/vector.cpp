#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdexcept>
#include "vector.h"

using namespace std;

// Default constructor
Vector::Vector() {
	capacity = 0;
	my_size = 0;
	array = new unsigned int[0];
};

// Constructor creates Vector which size elements to be hold
Vector::Vector(size_t size) {
	my_size = size;
	capacity = size;
	array = new unsigned int[capacity];

	// Set all values to zero
	//initiate(array);
	for(size_t i = 0; i < my_size; i++)
		array[i] = 0;
}

// Copy constructor
Vector::Vector(const Vector &v) {
	my_size = v.my_size;
	capacity = v.capacity;
	array = new unsigned int[capacity];

	for(size_t i = 0; i < my_size; i++) {
		array[i] = v[i];
	}
 	// memory secured??
}

Vector::~Vector() { delete [] array; }

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
	
	//memcpy(array, v.array, capacity * sizeof(unsigned int));
	for(size_t i = 0; i < my_size; i++)
		array[i] = v[i];
	
	return *this;
}

unsigned int Vector::size() const { return my_size; }

int main() {
    Vector a(7);
    cout << "Default constructor: a.size() = " << a.size() << endl;
    Vector b = a;
    cout << "Copy through copy constructor: b.size() = " << b.size() << endl;
   	b = b; 	// Error!!
   	cout << "Copy through assignment: b.size() = " << b.size() << endl;
   	b[0] = 1;
   	b[6] = 2;
   	// cout << "Array values [";
   	// for(int i = 0; i < b.size(); i++) cout << b[i] << ", ";
   	// cout << "]\n";

   	try {
   		int i = b[7];
   	} catch (std::out_of_range e) {
   		cout << e.what() << endl;
   	}

	return 0;

}