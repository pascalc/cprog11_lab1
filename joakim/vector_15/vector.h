#ifndef VECTOR_15_H
#define VECTOR_15_H

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <stdexcept>
#include <iostream>

using namespace std;

template<class T>
class Vector {
	public:
		typedef T *iterator;
		// Constructors
		Vector();
		explicit Vector(size_t size);
		Vector(size_t size, const T &val);
		Vector(const Vector<T> &v);
		// Deconstructor
		~Vector();

		// Functions
		const T operator[](size_t i) const;
		T& operator[](size_t i);
		Vector& operator=(const Vector<T> &vector);
		void push_back(const T &elem);	// Add element elem last in the vector
		void insert(size_t i, const T &elem);	// Insert element elem before index i	
		void erase(size_t i);	// Erase element at index i 
		void clear();	// Remove ALL elements in the vector
		// Should be const!
		unsigned size() const;	// Return number of elements in the vector.
		void sort(bool ascending); // Sort in asc/desc order. Default is asc
		void resize();	// Change capacity to meet requirments
		
	private:
		// Variables
		unsigned int capacity;		// capacity of the vector
		unsigned int my_size;		// size of the vector
		T* array;					// underlaying array of type T (generic)
};

// Default constructor
template <class T>
Vector<T>::Vector() {
	capacity = 0;
	my_size = 0;
	array = new T[0];
}

// Constructor creates Vector which size elements to be hold
template <class T>
Vector<T>::Vector(size_t size) {
	my_size = size;
	capacity = size;
	array = new T[capacity];
	
	for(size_t i = 0; i < my_size; i++)
		array[i] = T();
	//memset(array, T(), capacity * sizeof(T));
}

// Constructor creates Vector with size 'size' and initiates all elements to 'val'
template <class T>
Vector<T>::Vector(size_t size, const T &val) {
	my_size = size;
	capacity = size;
	array = new T[capacity];

	for(size_t i = 0; i < my_size; i++)
		array[i] = val;
	
	//memset(array, val, capacity * sizeof(T));

}

// Copy constructor
template <class T>
Vector<T>::Vector(const Vector<T> &v) {
	my_size = v.size;
	capacity = v.capacity;
	array = new T[capacity];
	
	for(size_t i = 0; i < my_size; i++)
		array[i] = v[i];
	//memcpy(array, v.array, capacity * sizeof(T));

	// memory secured??
}

template<class T>
Vector<T>::~Vector() { delete [] array; }

/** FUNCTION DECLARATIONS **/

template <class T>
const T Vector<T>::operator[](size_t index) const {
    if(index >= my_size || index < 0)
		throw std::out_of_range ("Trying to access index out of range");    	
    return array[index];
}

template <class T>
T& Vector<T>::operator[](size_t index) {
    if(index >= my_size || index < 0)
    	throw std::out_of_range ("Trying to access index out of range");
    	
    return array[index];
}

template <class T>
Vector<T> & Vector<T>::operator=(const Vector<T> &v) {
	if(this == &v) 
		return *this;
	
	my_size = v.my_size;
	capacity = v.capacity;
	array = new T[capacity];
	
	for(size_t i = 0; i < my_size; i++)
		array[i] = v[i];
	//memcpy(array, v.array, capacity * sizeof(T));
		
	return *this;
}

template <class T>
void Vector<T>::push_back(const T &elem) {
	// Check if enough capacity
	if(my_size <= capacity) 
		resize();
	
	array[my_size++] = elem; 
}

template <class T>
void Vector<T>::insert(size_t index, const T &elem) {
	if(index >= my_size || index < 0) 
		throw std::out_of_range("Trying to access index out of range");
	
	// If i is last index this functions equals push_back
	if(index == my_size) {
		push_back(elem);
		return;
	}

	// Check if enough capacity else resize
	if(my_size <= capacity ) 
		resize();
	
	// Copy everything from i to i+1 (zero or one index??)
	memcpy(&array[index+1], &array[index], (my_size) * sizeof(T));
	array[index] = elem;

	my_size++;
}

template <class T>
void Vector<T>::erase(size_t index) {
	array[index] = 0;
	// Copy all elements right of i to i-1
	memcpy(&array[index], &array[index+1], (my_size-1) *sizeof(T));
	my_size--;
}

template <class T>
void Vector<T>::clear() { memset(array, 0, my_size * sizeof(T)); my_size = 0; }

template <class T>
size_t Vector<T>::size() const { return my_size; }

template <class T>
void Vector<T>::resize() {
	std::cout << "\nresize()\n";
	capacity = capacity + ceil(my_size/2); 
	T *new_array = new T[capacity];
	for(size_t i = 0; i < capacity; i++) {
		if(i < my_size) {
			new_array[i] = array[i];
			} else {
				new_array[i] = 0;
			}
	}
 	//memcpy(new_array, array, my_size);
	delete [] array;
	array = new_array;
}

// template<class T>
// T * Vector<T>::iterator() {
// 	return array;
// }

template <class T>
void Vector<T>::sort(bool ascending = true) {
	//algorithm::sort(iterator(), iterator()+my_size);

	if(!ascending) {
		//reverse(iterator(), iterator()+my_size);
	}
}
#endif