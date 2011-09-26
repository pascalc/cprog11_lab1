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
		size_t size() const;	// Return number of elements in the vector.
		void sort(bool ascending); // Sort in asc/desc order. Default is asc
		void resize();	// Change capacity to meet requirments
		
	private:
		// Variables
		size_t capacity;		// capacity of the vector
		size_t my_size;			// size of the vector
		T* array;					// underlaying array of type T (generic)
		T *start, *end, *next;
};

//#endif ?

// Default constructor
template <class T>
Vector<T>::Vector() {
	capacity = 0;
	my_size = 0;
	array = new T[0];
	start = array;
	end = array;
}

// Constructor creates Vector which size elements to be hold
template <class T>
Vector<T>::Vector(size_t size) {
	my_size = size;
	capacity = size;
	array = new T[capacity];
	start = array;
	end = start + my_size;
	
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
	start = array;
	end = start + my_size;

	for(size_t i = 0; i < my_size; i++)
		array[i] = val;
	
	//memset(array, val, capacity * sizeof(T));

}

// Copy constructor
template <class T>
Vector<T>::Vector(const Vector<T> &v) {
	my_size = v.size();
	capacity = v.capacity;
	array = new T[capacity];
	start = array;
	end = start + my_size;
	
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
	
	start = array;
	end = end + 1;
	array[my_size++] = elem; 
	// start = end + my_size;
}

template <class T>
void Vector<T>::insert(size_t index, const T &elem) {
	if(index > my_size || index < 0)
		throw std::out_of_range("Trying to access index out of range");
	
	if(index == my_size || my_size == 0) {
		push_back(elem);
		return;
	}

	// Check if enough capacity else resize
	//resize requirement. if( [capacity - my_size] < 5
	if((capacity - my_size ) < 5)//if(my_size <= capacity ) 
		resize();
	
	//Copy everything from i to i+1 (zero or one index??)
	T *src_ = &array[index];
	T* dest_ = &array[index+1];
	size_t bytes_ = (my_size - index) * sizeof(T);
	memmove(&src_, &dest_, bytes_);
	array[index] = elem;

	my_size++;

}

template <class T>
void Vector<T>::erase(size_t index) {
	if(index >= my_size || index < 0) {
		throw std::out_of_range("Out or range!");
	}

	T *src_ = &array[index+1];
	T *dest_ = &array[index];
	size_t bytes_ = (my_size - index+1) * sizeof(T);
	memmove(src_, dest_, bytes_);
	
	array[--my_size] = 0;
}

template <class T>
void Vector<T>::clear() { 
	for(size_t i = 0; i < my_size; i++)
		array[i] = T();
	my_size = 0;
}

template <class T>
size_t Vector<T>::size() const { return my_size; }

template <class T>
void Vector<T>::resize() {
	std::cout << "\nresize()\n";
	size_t new_capacity = capacity + ceil(my_size/2) + 1; 
	cout << "cap/new_cap = " << capacity << "/" << new_capacity << endl;
	T *new_array = new T[new_capacity];
	for(size_t i = 0; i < new_capacity; i++) {
		if(i < my_size) {
			new_array[i] = array[i];
		} else {
			new_array[i] = 0;
		}
	}

 	//memcpy(new_array, array, capacity * sizeof(T));
	delete [] array;
	capacity = new_capacity;
	//cout << "\nnew_capacity = " << new_capacity << endl;
	array = new_array;
}

// template <class T>
// void Vector<T>::resize(size_t index) {
// 	size_t new_capacity = capacity + index + ceil(my_size/2) + 1;
// 	T *new_array = new T[new_capacity];
// 	for(size_t i = 0; i < new_capacity; i++) {
// 		if(i < my_size) {
// 			new_array[i] = array[i];
// 		} else {
// 			new_array[i] = 0;
// 		}
// 	}

// 	delete [] array;
// 	capacity = new_capacity;
// 	array = new_array;

// }

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